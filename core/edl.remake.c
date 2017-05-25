/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edl.remake.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertojo <tbertojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 13:05:18 by tbertojo          #+#    #+#             */
/*   Updated: 2017/04/21 22:12:34 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_mato(t_me *me, t_edl *edl, char *tmp, int a)
{
	int	v;

	v = 0;
	if ((int)ft_strlen(tmp) > a)
	{
		exec_mode(me, "cr");
		if ((edl->spos + edl->prompt_size) % me->width == 0)
			prepare_mline(me, ((ft_strlen(tmp) - a) / me->width) + 1, 0);
		else
			prepare_mline(me, ((ft_strlen(tmp) - a) / me->width) + 1, 1);
		while (v++ < ((edl->spos + edl->prompt_size) % me->width))
			exec_mode(me, "nd");
	}
	exec_mode(me, "sc");
	ft_putstr(tmp);
	exec_mode(me, "rc");
}

void	middle_write(t_me *me, t_edl *edl, char key)
{
	int		p;
	int		a;
	char	*tmp;

	p = 0;
	tmp = NULL;
	tmp = ft_strdup(&edl->line[(edl->spos + 1)]);
	exec_mode(me, "sc");
	ft_putchar(key);
	execute_move(me, edl, RIGHT, 0);
	p = ((((edl->spos + edl->prompt_size)) / me->width) + 1) * me->width;
	a = p - ((edl->spos + edl->prompt_size));
	if ((edl->spos + edl->prompt_size) % me->width == 0)
	{
		exec_mode(me, "do");
		exec_mode(me, "cr");
		ft_mato(me, edl, tmp, a);
	}
	else
		ft_mato(me, edl, tmp, a);
	free(tmp);
}
