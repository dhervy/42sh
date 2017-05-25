/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.dquotes.utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 15:15:08 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 02:12:54 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_ok_quote(char *s)
{
	int	i;
	int	d;

	i = -1;
	d = 0;
	while (s[++i])
	{
		if (s[i] == '\'' && nescape(s, i))
		{
			while (s[++i] && s[i] != '\'')
				if (nescape(s, i) && s[i] == '\"')
					return (0);
		}
		if (s[i] && s[i] == '\"' && nescape(s, i))
		{
			while (s[++i] && s[i] != '\"')
				if (nescape(s, i) && s[i] == '\'')
					return (0);
		}
	}
	return (1);
}

void	down_hist(t_me *me, t_edl *edl, t_hist *t, t_hist *end_hist)
{
	int c;

	c = -1;
	(void)end_hist;
	while (t && t->prev && t->select == 0)
		t = t->prev;
	if (t->select == 0)
		return ;
	t->select = 0;
	if (t->next)
		t = t->next;
	else
	{
		restore_pos(me, (t_vec){edl->pos.x - edl->prompt_size, edl->pos.y});
		exec_mode(me, "cd");
		edl->line ? free(edl->line) : 0;
		edl->line = 0;
		edl->emode = EDIT;
		me->l = hi_end(me->hi);
		edl->pos.x = edl->prompt_size;
		edl->pos.y = 0;
		edl->spos = 0;
		return ;
	}
	down_hist2(me, edl, t, c);
}

void	switch_history3(t_me *me, t_edl *edl, t_hist *t, int c)
{
	restore_pos(me, (t_vec){edl->pos.x - edl->prompt_size, edl->pos.y});
	edl->pos.x = edl->prompt_size;
	edl->pos.y = 0;
	edl->spos = 0;
	ft_putstr_fd(tgetstr("cd", NULL), me->fd);
	c = -1;
	edl->line ? free(edl->line) : 0;
	edl->line = NULL;
	while (t && t->name && t->name[++c])
		insert_key(me, edl, t->name[c]);
	t->select = 1;
	edl->emode = NAV;
	me->l = t;
}

t_hist	*switch_history2(t_hist *t)
{
	t->select = 0;
	return (t->prev);
}

void	switch_history(t_me *me, t_edl *edl, int key)
{
	t_hist	*t;
	t_hist	*end_hist;

	if (me->hi)
	{
		t = me->hi;
		while (t && t->next)
			t = t->next;
		end_hist = t;
		if (edl && key == UP)
		{
			while (t && t->prev && t->select == 0)
				t = t->prev;
			if (t->select == 0)
				t = end_hist;
			else if (!t->prev)
				return ;
			else
				t = switch_history2(t);
			switch_history3(me, edl, t, 0);
		}
		else if (edl && key == DOWN)
			down_hist(me, edl, end_hist, t);
	}
}
