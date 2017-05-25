/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 15:16:41 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/31 15:13:33 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*clean_line(char *line)
{
	int		i;
	int		in;

	i = -1;
	in = 0;
	while (line[++i])
	{
		if (line[i] == '\"')
			in = in ? 0 : 1;
		if (line[i] == ';' && !in)
		{
			line = string_inject(line, " ; ", i++, 1);
		}
		if (!line)
			break ;
	}
	return (line);
}

char	*clean_quotes(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			line = cdel(line, i);
			i = 0;
		}
		if (!line)
			break ;
	}
	return (line);
}

void	push_cmd(t_me *me, int i)
{
	t_cmd	*new;
	t_cmd	*at;
	char	**t;
	char	**afd;

	if (!me->sh_c || !me->sh_c[i] ||
		!me || !(new = malloc(sizeof(t_cmd))))
		return ;
	new->token = get_token(me->sh_c[i]);
	t = tab_dup(me->sh_c);
	clean_cmd_data(t, i);
	init_mcmd(new, t[i]);
	afd = get_args(me, new, t, i);
	new->afd = afd ? create_afd_list(afd) : 0;
	afd ? tab_free(afd) : 0;
	t ? tab_free(t) : 0;
	if (me->cmds)
	{
		at = me->cmds;
		while (at->next)
			at = at->next;
		at->next = new;
	}
	else
		me->cmds = new;
}

void	push_deli(t_me *me, char *cmd, int i)
{
	t_cmd	*new;
	t_cmd	*at;

	(void)i;
	if (!cmd || !me || !(new = malloc(sizeof(t_cmd))))
		return ;
	new->name = ft_strdup(cmd);
	new->token = get_token(cmd);
	new->args = 0;
	new->afd = 0;
	new->next = 0;
	if (me->cmds)
	{
		at = me->cmds;
		while (at->next)
			at = at->next;
		at->next = new;
	}
	else
		me->cmds = new;
}

void	cmds_free(t_me *me)
{
	t_cmd	*curs;
	t_cmd	*t;

	curs = me->cmds;
	while (curs)
	{
		t = curs->next;
		tab_free(curs->args);
		if (curs->afd)
			free_afds(curs->afd);
		free(curs->name);
		free(curs);
		curs = t;
	}
	me->cmds = 0;
}
