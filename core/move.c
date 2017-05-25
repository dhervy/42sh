/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertojo <tbertojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:21:07 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/25 18:28:41 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		insert_key(t_me *me, t_edl *edl, char key)
{
	edl->emode = EDIT;
	edl->line = add_key(edl->line, key, edl->spos);
	if ((edl->spos + 1) == (int)ft_strlen(edl->line))
	{
		ft_putchar(key);
		execute_move(me, edl, RIGHT, 0);
	}
	else
		middle_write(me, edl, key);
	return (1);
}

int		insert_nkey(t_me *me, t_edl *edl, char key, int times)
{
	while (times-- > 0)
		insert_key(me, edl, key);
	return (1);
}

void	execute_move2(t_me *me, t_edl *edl, int key, int move)
{
	int tmp;

	(void)move;
	if (key == DOWN && edl->line &&
		(edl->spos + me->width) <= (int)ft_strlen(edl->line))
	{
		tmp = (edl->pos.x + me->width) % me->width;
		edl->spos += me->width;
		exec_mode(me, "do");
		edl->pos.y += 1;
		edl->pos.x = tmp;
		exec_tmode(me, "nd", tmp);
	}
	if (key == UP && edl->pos.y > 0 &&
		(edl->spos - me->width) >= 0)
	{
		exec_mode(me, "up");
		edl->pos.y -= 1;
		edl->spos -= (me->width);
	}
}

void	execute_special_move(t_me *me, t_edl *edl, int key, int move)
{
	if (key == RIGHT && edl->line && edl->spos < (int)ft_strlen(edl->line))
	{
		if (edl->pos.x + 1 < me->width && (++(edl->spos)) > -1)
		{
			++(edl->pos.x);
			move ? exec_mode(me, "nd") : 0;
		}
		else if (++(edl->spos) > -1)
		{
			edl->pos.y += 1;
			edl->pos.x = 0;
			move ? exec_mode(me, "do") : 0;
		}
	}
}

void	execute_move(t_me *me, t_edl *edl, int key, int move)
{
	if (key == LEFT)
	{
		if (edl->spos > 0 && edl->pos.x > 0 &&
			(--(edl->spos)) > -1)
		{
			--(edl->pos.x);
			move ? exec_mode(me, "le") : 0;
		}
		else if (edl->spos > 0 && edl->pos.y > 0)
		{
			--(edl->pos.y);
			--(edl->spos);
			edl->pos.x = me->width - 1;
			move ? exec_mode(me, "up") : 0;
			move ? exec_tmode(me, "nd", W_MAX) : 0;
		}
	}
	execute_special_move(me, edl, key, move);
	if (key == UP)
		switch_history(me, edl, key);
	if (key == DOWN)
		switch_history(me, edl, key);
}
