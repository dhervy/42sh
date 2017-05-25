/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_updown2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <dhervy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:31:09 by dhervy            #+#    #+#             */
/*   Updated: 2017/05/03 17:32:32 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_check_bn(char *line, int pos_x)
{
	int		i;

	i = 0;
	while (i <= pos_x)
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		ft_check_first_line_left(t_me *me)
{
	int		i;
	int		nbr;
	int		c;

	i = 0;
	nbr = 0;
	c = 4;
	while (i < me->edl.spos)
	{
		c++;
		if (me->edl.line[i] == '\n')
		{
			nbr++;
			c = 0;
		}
		if (c == me->width)
		{
			c = 0;
			nbr++;
		}
		i++;
	}
	return (nbr);
}

int		ft_count_move_left(t_me *me)
{
	int		i;
	int		nbr;

	i = me->edl.spos - 2;
	while (i > 0 && me->edl.line[i] != '\n')
		i--;
	nbr = ((me->edl.spos - 2) - i) % me->width;
	if (ft_check_first_line_left(me) == 0)
		nbr += 5;
	exec_mode(me, "up");
	i = 0;
	while (i++ < me->width)
		exec_mode(me, "le");
	while (nbr-- >= 0)
		exec_mode(me, "nd");
	return (1);
}

int		ft_check_move_left(t_me *me)
{
	int		i;

	i = me->edl.spos - 1;
	if (!ft_check_bn(me->edl.line, me->edl.spos))
	{
		if ((me->edl.spos + 9) % me->width == 0)
			return (2);
		else
			return (0);
	}
	else
	{
		while (me->edl.line[i] != '\n')
			i--;
		if ((me->edl.spos - i) % me->width == 0)
			return (2);
		else if (me->edl.line[me->edl.spos] == '\n')
			return (ft_count_move_left(me));
		else
			return (0);
	}
}

int		ft_move_left(t_me *me)
{
	int		i;
	int		ret;

	i = 0;
	ret = -1;
	me->edl.spos--;
	if ((ret = ft_check_move_left(me)) != 0)
	{
		if (ret == 2)
		{
			exec_mode(me, "up");
			while (i++ < me->width)
				exec_mode(me, "nd");
		}
	}
	else
		exec_mode(me, "le");
	return (0);
}
