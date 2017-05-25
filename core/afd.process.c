/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   afd.process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:12:37 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/17 14:02:52 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		afd_perror(int e, int new)
{
	if (e == -1)
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putnbr_fd(new, 2);
		ft_putstr_fd(": bad file descriptor\n", 2);
		return (-1);
	}
	return (1);
}

int		process_afds(t_afd *list)
{
	t_afd	*c;

	if (!list)
		return (1);
	if (prepare_afds(list) == -1)
		return (-1);
	c = list;
	while (c && ft_strcmp(c->str, ";") &&
	ft_strcmp(c->str, "&&") && ft_strcmp(c->str, "||"))
	{
		if ((c->type == ADD || c->type == OVER))
		{
			if (afd_perror(dup2(c->new, c->old), c->new) == -1)
				return (-1);
		}
		if (c->type == CLOSE)
			close(c->old);
		c = c->next;
	}
	return (1);
}
