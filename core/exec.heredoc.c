/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertojo <tbertojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:35:08 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/13 20:15:41 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		execute_henter(t_me *me, t_edl *edl, long int key)
{
	if (key == ENTER)
	{
		edl->emode = EDIT;
		if (!edl->line || ft_strcmp(edl->line, edl->end))
		{
			edl->line = join_free(edl->line, ft_strdup("\n"));
			edl->t = join_free(edl->t, edl->line);
		}
		else if (edl->line)
		{
			exec_mode(me, "do");
			return (0);
		}
		ft_putstr_fd(tgetstr("do", 0), me->fd);
		mprompt(me, edl->type, 1);
		edl->line = 0;
		me->trees = 0;
		me->go = 1;
		edl->spos = 0;
		edl->pos.x = edl->prompt_size;
		edl->pos.y = 0;
	}
	return (1);
}

int		execute_hkey(t_me *me, t_edl *edl, long int key)
{
	if (key == 4)
	{
		exec_mode(me, "do");
		return (-42);
	}
	if (!execute_henter(me, edl, key))
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

char	*hedl_loop(t_me *me, char *end)
{
	long int	k;
	t_edl		edl;

	edl.spos = 0;
	edl.line = 0;
	edl.prompt_size = 8;
	edl.pos.x = edl.prompt_size;
	edl.pos.y = 0;
	edl.type = HDOC;
	edl.t = 0;
	edl.select[0] = -1;
	edl.select[1] = -1;
	edl.clipboard = 0;
	edl.end = end;
	mprompt(me, edl.type, 1);
	while (42 && edl.end)
	{
		k = 0;
		read(0, (char*)(&k), 6);
		get_wterm(me);
		if (execute_hkey(me, &edl, k) == -42)
			return (edl.t);
	}
	return (0);
}

void	heredoc_loop(t_me *me, t_node *curs)
{
	char	*out;

	out = 0;
	init_term(me);
	curs->thdoc = hedl_loop(me, curs->cmd->name);
}
