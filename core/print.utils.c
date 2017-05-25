/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:46:40 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/07 14:47:54 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	psc(char *s, char *c, int fd)
{
	ft_putstr_fd("\033[", fd);
	ft_putstr_fd(c, fd);
	ft_putstr_fd("m", fd);
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\033[0m", fd);
}

void	print_cmds(t_cmd *c)
{
	while (c)
	{
		tab_print(c->args);
		ft_putendl("--");
		c = c->next;
	}
}
