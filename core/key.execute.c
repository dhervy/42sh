/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:58:39 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 17:07:59 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	execute_special(t_me *me, t_edl *edl, long int key)
{
	int ox[2];

	if (key == CL)
	{
		ox[0] = edl->spos;
		ox[1] = edl->pos.x;
		exec_mode(me, "cl");
		exec_tmode(me, "nd", edl->prompt_size);
		edl->spos = ox[0];
		edl->pos.x = ox[1];
		edl->pos.y = 0;
		refresh_pprompt(me, edl);
		ox[1] -= (edl->prompt_size + 1);
		while (ox[1]-- >= 0)
			exec_mode(me, "nd");
	}
	else if (key == ESC)
	{
		edl->ccmode = edl->ccmode ? 0 : 1;
		edl->select[0] = edl->ccmode ? edl->spos : -1;
		edl->select[1] = edl->ccmode ? edl->spos : -1;
		refresh_pprompt(me, edl);
	}
}

void	execute_paste_key(t_me *me, t_edl *edl)
{
	int i;

	i = -1;
	while (edl->clipboard[++i])
		insert_key(me, edl, (char)edl->clipboard[i]);
	restore_pos(me, (t_vec){edl->pos.x - edl->prompt_size, edl->pos.y});
	refresh_pprompt(me, edl);
	edl->spos = 0;
	edl->pos.x = edl->prompt_size;
	edl->pos.y = 0;
	edl->select[0] = -1;
	edl->select[1] = -1;
}

void	execute_key_end(t_me *me, t_edl *edl, long int key)
{
	if (key == OLEFT || key == ORIGHT)
		pass_chars(me, edl, key);
	else if (key == OUP || key == ODOWN)
		move_updown(me, key);
	else if (key == CL || key == ESC)
		execute_special(me, edl, key);
	else if (edl->ccmode && edl->line)
		execute_select(me, edl, key);
	else
		execute_move(me, edl, key, 1);
	if (key == OV && edl->clipboard)
		execute_paste_key(me, edl);
}

int		execute_key(t_me *me, t_edl *edl, long int key)
{
	if (key == 4 && !edl->line)
		sig_exit_signal(me);
	if (key == ENTER)
		execute_enter_key(me, edl);
	else if (!is_key(key) || key == SPC)
		key == SPC || ft_isprint((char)key) ?
		insert_key(me, edl, (char)key) : 0;
	else if (key == TAB)
		get_autocomplet(me, edl);
	else if (key == DEL)
		delete_char(me, edl);
	else if (key == HOME)
		prompt_start(me, edl);
	else if (key == END)
		prompt_end(me, edl);
	else
		execute_key_end(me, edl, key);
	return (is_key(key));
}
