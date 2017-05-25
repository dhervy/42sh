/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:45:39 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/17 14:03:09 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	putstr_special_fd(char *s, int fd)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\n')
			ft_putstr_fd("\\n", fd);
		else if (s[i] != '\\')
			ft_putchar_fd(s[i], fd);
	}
}

int		merror(t_me *me, char *cmd, int keycode)
{
	(void)me;
	ft_putstr_fd("42sh: ", 2);
	cmd && keycode != 3 ? putstr_special_fd(cmd, 2) : 0;
	if (keycode == 1)
		ft_putstr_fd(": command not found", 2);
	if (keycode == 2)
		ft_putstr_fd(": No such file or directory", 2);
	if (keycode == 3)
	{
		ft_putstr_fd("permission denied: ", 2);
		cmd ? ft_putstr_fd(cmd, 2) : 0;
	}
	ft_putchar_fd('\n', 2);
	return (1);
}
