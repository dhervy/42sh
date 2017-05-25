/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertojo <tbertojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:25:22 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/13 20:24:25 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	restore_pos(t_me *me, t_vec pos)
{
	while (--pos.x >= 0)
		exec_mode(me, "le");
	while (--pos.y >= 0)
		exec_mode(me, "up");
}

void	refresh_pprompt(t_me *me, t_edl *edl)
{
	int		i;

	exec_mode(me, "sc");
	restore_pos(me, (t_vec){edl->pos.x, edl->pos.y});
	mprompt(me, edl->type, me->go);
	exec_mode(me, "cd");
	i = -1;
	while (edl->line && edl->line[++i])
	{
		i >= edl->select[0] &&
		i <= edl->select[1] ? exec_mode(me, "mr") : 0;
		ft_putchar(edl->line[i]);
		i >= edl->select[0] &&
		i <= edl->select[1] ? exec_mode(me, "me") : 0;
	}
	exec_mode(me, "rc");
}

void	prompt_start(t_me *me, t_edl *edl)
{
	t_vec p;
	t_vec op;

	op = (t_vec){(int)-edl->prompt_size, (int)0};
	p = vec_add(edl->pos, op);
	edl->pos.x = edl->prompt_size;
	edl->pos.y = 0;
	edl->spos = 0;
	restore_pos(me, p);
}

void	prompt_end(t_me *me, t_edl *edl)
{
	while (edl && edl->line && edl->line[edl->spos])
	{
		execute_move(me, edl, RIGHT, 1);
	}
}

void	prepare_mline(t_me *me, int n, int o)
{
	int i;

	i = -1;
	while (++i < n)
	{
		exec_mode(me, "do");
		if (o == 1)
			exec_mode(me, "ce");
	}
	i = -1;
	while (++i < n)
		exec_mode(me, "up");
}
