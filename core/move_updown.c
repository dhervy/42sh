/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_updown.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <dhervy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:27:09 by dhervy            #+#    #+#             */
/*   Updated: 2017/05/03 17:33:17 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_check_move_right(t_me *me)
{
	int		i;

	i = me->edl.spos - 1;
	while (i > 0 && me->edl.line[i] != '\n')
		i--;
	if (i == 0)
	{
		if ((8 + me->edl.spos) % me->width == 0)
			return (1);
		else
			return (0);
	}
	else
	{
		if ((me->edl.spos - i) % me->width == 0)
			return (1);
		else
			return (0);
	}
}

int		ft_move_right_quote(t_me *me)
{
	int		i;

	i = 0;
	while (me->edl.line[i] && me->edl.line[i] != '\n')
		i++;
	if (me->edl.line[i] == '\0')
	{
		if ((8 + me->edl.spos) % me->width == 0)
			return (1);
		else
			return (0);
	}
	else
	{
		if (me->edl.line[me->edl.spos - 1] == '\n')
			return (1);
		else if (ft_check_move_right(me))
			return (1);
		else
			return (0);
	}
}

int		ft_move_right(t_me *me)
{
	me->edl.spos++;
	if (ft_move_right_quote(me))
	{
		exec_mode(me, "do");
	}
	else
		exec_mode(me, "nd");
	return (1);
}

void	move_updown(t_me *me, long int buf)
{
	int		nbr;

	if (buf == OUP && (me->edl.spos - me->width) >= 0)
	{
		nbr = me->edl.spos - me->width;
		if (nbr < 0)
			nbr = 0;
		while (me->edl.spos > nbr)
			ft_move_left(me);
		me->edl.pos.y--;
	}
	if (buf == ODOWN && (me->edl.spos + me->width) < \
	(int)ft_strlen(me->edl.line))
	{
		nbr = me->edl.spos + me->width;
		if (me->edl.line && nbr > (int)ft_strlen(me->edl.line) - 1)
			nbr = ft_strlen(me->edl.line) - 1;
		while (me->edl.spos < nbr)
			ft_move_right(me);
		me->edl.pos.y++;
	}
}
