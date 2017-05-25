/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:45:49 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/06 10:35:40 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		errors(int e, char *app, char *s, t_cmd *cmd)
{
	(void)s;
	(void)cmd;
	if (e == 'e')
	{
		ft_putstr_fd("setenv: ", 2);
		ft_putstr_fd(app, 2);
		ft_putstr_fd(": wrong number of arguments\n", 2);
	}
	return (1);
}
