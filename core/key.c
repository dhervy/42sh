/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:00:45 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 17:16:22 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	delete_char(t_me *me, t_edl *edl)
{
	if (!edl->line || edl->spos < 1)
		return ;
	if (edl->spos > 0)
	{
		edl->line = delete_key(edl->line, edl->spos - 1);
		execute_move(me, edl, LEFT, 1);
	}
	refresh_pprompt(me, edl);
}

void	pass_chars(t_me *me, t_edl *edl, long int key)
{
	int io;

	if (!edl || !edl->line)
		return ;
	io = 1;
	if (edl->line && edl->line[edl->spos])
		io = edl->line[edl->spos] == ' ' ? 1 : 0;
	if (key == ORIGHT || key == OLEFT)
	{
		while (edl->spos < (int)ft_strlen(edl->line) &&
				(edl->spos > 0 || (key == ORIGHT && !edl->spos)) &&
			((io && edl->line[edl->spos] == ' ') ||
			(!io && edl->line[edl->spos] != ' ')))
			execute_move(me, edl, key == ORIGHT ? RIGHT : LEFT, 1);
		if (key == OLEFT && edl->spos == (int)ft_strlen(edl->line))
			execute_move(me, edl, key == ORIGHT ? RIGHT : LEFT, 1);
	}
}

void	edl_default(t_edl *edl)
{
	if (!edl)
		return ;
	edl->line = 0;
	edl->prompt_size = 8;
	edl->spos = 0;
	edl->pos.x = edl->prompt_size;
	edl->pos.y = 0;
	edl->select[0] = -1;
	edl->select[1] = -1;
	edl->clipboard ? free(edl->clipboard) : 0;
	edl->clipboard = 0;
}
