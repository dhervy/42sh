/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertojo <tbertojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 02:20:01 by tbertojo          #+#    #+#             */
/*   Updated: 2017/05/03 02:21:34 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	clean_history(t_me *me)
{
	t_hist *tmp;
	t_hist *tmp2;

	tmp = me->hi;
	while (tmp)
	{
		free(tmp->name);
		tmp->name = NULL;
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	me->hi = NULL;
}

void	find_index_max(t_me *me, int *i)
{
	t_hist	*tmp;

	*i = 0;
	tmp = me->hi;
	while (tmp && tmp->next)
		tmp = tmp->next;
	*i = tmp ? intlen((long int)tmp->index + 1) + 1 : 0;
}

void	affi_hist_index(t_hist *tmp, int i, int fd)
{
	int	t;

	t = 0;
	while (t++ < (i - intlen((long int)tmp->index + 1)))
		ft_putchar_fd(' ', fd);
	ft_putnbr_fd(tmp->index + 1, fd);
	ft_putchar_fd(' ', fd);
}

t_hist	*affi_end_history2(t_hist *tmp, int r)
{
	while (tmp && tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->prev)
	{
		r = r > 0 ? r - 1 : r;
		if (!r)
			break ;
		tmp = tmp->prev;
	}
	return (tmp);
}

void	affi_end_history(t_me *me, int r, int fd, int affindex)
{
	t_hist	*tmp;
	int		i;

	find_index_max(me, &i);
	tmp = me->hi;
	tmp = affi_end_history2(tmp, r);
	while (tmp)
	{
		if (r)
		{
			if (affindex)
				affi_hist_index(tmp, i, fd);
			if ((!affindex && !tmp->inlist) || (affindex))
			{
				ft_putendl_fd(tmp->name, fd);
				if (!affindex)
					tmp->inlist = 1;
			}
			r = r > 0 ? r - 1 : r;
		}
		if (r == 0)
			break ;
		tmp = tmp->next;
	}
}
