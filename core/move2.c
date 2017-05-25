/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:29:09 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 02:16:42 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_hist	*hi_end(t_hist *start)
{
	while (start->next)
		start = start->next;
	return (start);
}

void	switch_history_end_2(t_me *me, t_edl *edl)
{
	edl->emode = EDIT;
	me->l = hi_end(me->hi);
	edl->pos.x = edl->prompt_size;
	edl->pos.y = 0;
	edl->spos = 0;
	edl->line ? free(edl->line) : 0;
	edl->line = 0;
}

int		switch_history_end(t_hist *t, t_me *me, t_edl *edl, long int key)
{
	if (t && t->name)
	{
		edl->emode = NAV;
		restore_pos(me, (t_vec){edl->pos.x - edl->prompt_size, edl->pos.y});
		exec_mode(me, "cd");
		edl->pos.x = edl->prompt_size;
		edl->pos.y = 0;
		edl->spos = 0;
		me->l = t;
		edl->line ? free(edl->line) : 0;
		edl->line = 0;
		return (1);
	}
	else if (key == DOWN && edl->line)
	{
		restore_pos(me, (t_vec){edl->pos.x - edl->prompt_size, edl->pos.y});
		exec_mode(me, "cd");
		switch_history_end_2(me, edl);
		return (1);
	}
	return (0);
}

int		str_headmatch(char *s1, char *head)
{
	int i;

	i = -1;
	if (ft_strlen(s1) < ft_strlen(head))
		return (0);
	while (s1[++i] && head[i])
		if (s1[i] != head[i])
			return (0);
	return (1);
}

t_hist	*find_match(t_me *me, t_edl *edl, char *s, char side)
{
	t_hist *c;

	c = me->l;
	while (c)
	{
		if (c->name && ft_strcmp(c->name, edl->line) &&
			str_headmatch(c->name, s))
		{
			return (c);
		}
		c = side == 'n' ? c->next : c->prev;
	}
	return (0);
}
