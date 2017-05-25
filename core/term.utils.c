/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:39:50 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/03 16:48:51 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		mputs(int c)
{
	ft_putchar(c);
	return (1);
}

int		exec_mode(t_me *me, char *s)
{
	char	*res;

	if ((res = tgetstr(s, 0)))
	{
		ft_putstr_fd(res, me->fd);
		return (1);
	}
	return (0);
}

int		exec_tmode(t_me *me, char *s, int n)
{
	char	*res;
	int		i;

	if ((res = tgetstr(s, 0)))
	{
		i = -1;
		while (++i < n)
			ft_putstr_fd(res, me->fd);
		return (1);
	}
	return (0);
}

int		exec_to(int x, int y)
{
	char	*res;

	if ((res = tgetstr("cm", 0)))
	{
		tputs(tgoto(res, -1 + x, -1 + y), 0, &mputs);
		return (1);
	}
	return (0);
}
