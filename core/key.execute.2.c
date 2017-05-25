/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.execute.2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:10:29 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/02 14:58:32 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	execute_ocpy(t_me *me, t_edl *edl)
{
	edl->clipboard ? free(me->edl.clipboard) : 0;
	edl->clipboard = 0;
	edl->clipboard = cut_clipboard(edl);
	restore_pos(me, (t_vec){edl->pos.x - edl->prompt_size, edl->pos.y});
	edl->spos = 0;
	edl->pos.x = edl->prompt_size;
	edl->pos.y = 0;
	edl->select[0] = -1;
	edl->select[1] = -1;
}

void	execute_select(t_me *me, t_edl *edl, long int key)
{
	key == RIGHT && edl->select[1] < (int)ft_strlen(edl->line) ?
	++edl->select[1] : 0;
	key == LEFT && edl->select[0] > 0 ?
	--edl->select[0] : 0;
	if (key == OX)
	{
		edl->clipboard ? free(me->edl.clipboard) : 0;
		edl->clipboard = 0;
		if ((edl->clipboard = cut_clipboard(edl)))
			edl->line = msub_string(edl->line, edl->select[0], edl->select[1]);
		edl->ccmode = 0;
		restore_pos(me, (t_vec){edl->pos.x - edl->prompt_size, edl->pos.y});
		edl->spos = 0;
		edl->pos.x = edl->prompt_size;
		edl->pos.y = 0;
		edl->select[0] = -1;
		edl->select[1] = -1;
	}
	else if (key == OC)
	{
		execute_ocpy(me, edl);
	}
	refresh_pprompt(me, edl);
}

int		isin_hist(t_hist *l, char *name, int range)
{
	int i;

	i = -1;
	if (l)
	{
		while (l && ++i < range)
		{
			if (!ft_strcmp(l->name, name))
				return (1);
			l = l->next;
		}
	}
	return (0);
}

void	execute_useless(t_me *me, t_edl *edl)
{
	exit_term(me);
	if (edl->line)
		execute_line(me);
	if (!init_term(me))
		sig_exit_signal(me);
}

void	execute_enter_key(t_me *me, t_edl *edl)
{
	restor_select(me);
	if (!edl || !edl->line)
		me->go = 1;
	if ((edl->emode = EDIT) == EDIT && !me)
		return ;
	g_sigs.me->stop_edl = 0;
	if (me->width > 0)
		exec_tmode(me, "do", (1 - edl->pos.y) + (edl->line ?
		(((int)ft_strlen(edl->line) + edl->prompt_size - 1) / me->width) : 0));
	else
		exec_mode(me, "do");
	if (edl->line && !isin_hist(me->l, edl->line, 1))
		push_hist(me, edl->line);
	execute_useless(me, edl);
	if (!me->stop_edl)
		mprompt(me, edl->type, me->go);
	else
		g_sigs.me->stop_edl = 0;
	end_execute_enter(me, edl);
}
