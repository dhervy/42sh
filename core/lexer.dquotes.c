/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.dquotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 14:49:08 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 15:35:03 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		execute_qenter(t_me *me, t_edl *edl, char *last, char **qtype)
{
	execute_qenter_do(me, edl);
	edl->emode = EDIT;
	edl->type != 4 ? edl->t = join_free(edl->t, ft_strdup("\n")) : 0;
	if (((!ft_strcmp("\\", *qtype) && (!edl->line || \
	edl->line[ft_strlen(edl->line) - 1] != '\\' || \
	(edl->line[ft_strlen(edl->line) - 1] == '\\' && \
	!nescape(edl->line, ft_strlen(edl->line) - 1)))) || (edl->line && \
	ft_strcmp("\\", *qtype) && ((last = last_one(me, edl, edl->line, qtype)) ||\
	!ft_strcmp(edl->line, *qtype)))))
	{
		edl->type == 4 ? last = ft_strdup(edl->line) : 0;
		edl->line ? free(edl->line) : 0;
		edl->t = join_free(edl->t, last ? last : 0);
		return (1);
	}
	else if (edl->line)
	{
		edl->type == 4 ? edl->line[ft_strlen(edl->line) - 1] = 0 : 0;
		edl->t = join_free(edl->t, edl->line);
	}
	execute_qenter_init(me, edl);
	return (0);
}

int		execute_qkey(t_me *me, t_edl *edl, long int key, char **qtype)
{
	char	*last;

	last = 0;
	if (!edl)
		return (-1);
	if (key == ENTER)
		if (execute_qenter(me, edl, last, qtype))
			return (-42);
	if (!is_key(key) || key == SPC)
		key == SPC || ft_isprint((char)key) ?
		insert_key(me, edl, (char)key) : 0;
	if (key == DEL)
		delete_char(me, edl);
	else if (key == HOME)
		prompt_start(me, edl);
	else if (key == END)
		prompt_end(me, edl);
	else if (key == OLEFT || key == ORIGHT)
		pass_chars(me, edl, key);
	else
		execute_move(me, edl, key, 1);
	return (1);
}

int		dquote_loop(t_me *me, t_edl *edl, char **qtype)
{
	long int k;

	while (42 && !me->stop_edl)
	{
		k = 0;
		read(0, (char*)(&k), 6);
		get_wterm(me);
		if (execute_qkey(me, edl, k, qtype) == -42)
		{
			signal(SIGINT, (void(*)())sig_int);
			g_sigs.tmp = 0;
			return (1);
		}
	}
	return (0);
}

void	dquote_gnl_init(t_edl *edl)
{
	edl->spos = 0;
	edl->line = 0;
	edl->prompt_size = 8;
	edl->pos.x = edl->prompt_size;
	edl->pos.y = 0;
	edl->select[0] = -1;
	edl->select[1] = -1;
	edl->clipboard = 0;
	edl->t = 0;
}

char	*dquote_gnl(t_me *me, char **qtype)
{
	t_edl	edl;

	if (!*qtype)
		return (0);
	g_sigs.tmp = &edl;
	dquote_gnl_init(&edl);
	me->stop_edl = 0;
	if (!ft_strcmp(*qtype, "\\"))
		edl.type = BACKS;
	else
		edl.type = !ft_strcmp(*qtype, "\"") ? DQUOT : SQUOT;
	signal(SIGINT, (void(*)())sig_int_quote);
	edl.end = 0;
	mprompt(me, edl.type, 1);
	if (dquote_loop(me, &edl, qtype))
		return (clean_equot(edl.t));
	g_sigs.tmp = 0;
	signal(SIGINT, (void(*)())sig_int);
	return (0);
}
