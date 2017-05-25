/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:33:05 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/13 12:14:00 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	init_core_end(t_me *me)
{
	if (!me)
		return ;
	me->prank = 0;
	me->cmds = 0;
	me->hi = 0;
	me->l = 0;
	me->pprompt = 1;
	g_sigs.tmp = 0;
	me->a_fd = 0;
	me->edl.emode = EDIT;
	me->edl.type = LINE;
	me->edl.t = 0;
	me->edl.end = 0;
	me->pe = 0;
	me->trees = 0;
	me->go = 1;
	g_sigs.me = me;
}

int		get_wterm(t_me *me)
{
	struct winsize	wlen;
	int				r;

	if ((ioctl(0, TIOCGWINSZ, &wlen)) == -1)
		return (0);
	r = 1;
	if (wlen.ws_col != me->width ||
		me->height != wlen.ws_row)
		r = 1;
	me->width = wlen.ws_col;
	me->height = wlen.ws_row;
	return (r);
}

int		init_termios(t_me *me)
{
	if (tgetent(NULL, me->name_term) == -1)
		return (0);
	if (tcgetattr(0, &me->term) == -1)
		return (0);
	me->term.c_lflag &= ~(ICANON);
	me->term.c_lflag &= ~(ECHO);
	me->term.c_cc[VMIN] = 1;
	me->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &(me->term)) == -1)
		return (0);
	return (1);
}

int		exit_term(t_me *me)
{
	exec_mode(me, "ve");
	close(me->fd);
	if (tcsetattr(0, 0, &me->save) == -1)
		return (-1);
	return (0);
}

int		init_term(t_me *me)
{
	if ((me->fd = open(ttyname(0), O_RDWR)) == -1)
	{
		ft_putstr_fd("error", 2);
		return (0);
	}
	if (!init_termios(me))
		return (0);
	return (1);
}
