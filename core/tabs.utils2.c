/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs.utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:56:22 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/21 22:14:44 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	tab_print(char **t)
{
	int	a;

	a = -1;
	while (t[++a])
	{
		ft_putstr_fd(t[a], 2);
		ft_putstr_fd("\n", 2);
	}
}

int		tab_free(char **t)
{
	int	a;

	a = 0;
	while (t && t[a])
		free(t[a++]);
	if (t)
		free(t);
	return (1);
}

int		tab_nfree(char **t, int n)
{
	int	a;

	a = 0;
	while (t && a <= n)
	{
		t[a] ? free(t[a]) : 0;
		++a;
	}
	if (t)
		free(t);
	return (1);
}

char	**tab_nset(char **t, int n)
{
	int	a;

	a = 0;
	while (t && a <= n)
	{
		t[a] = 0;
		++a;
	}
	return (t);
}

int		tab_size(char **t)
{
	int	a;

	a = 0;
	while (t && t[a])
		a++;
	return (a);
}
