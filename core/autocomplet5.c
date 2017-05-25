/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplet5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:01:21 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/26 17:01:41 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_putcolor(char const *s, char *color)
{
	ft_putstr(color);
	ft_putstr(s);
	ft_putstr("\033[0m");
}

void	ft_putspace(int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		ft_putchar(' ');
		i++;
	}
}

void	ft_auto_free(t_auto **lsauto, char *string, char *path, char *debut)
{
	t_auto	*tmp;
	t_auto	*tmp2;

	free(string);
	free(path);
	free(debut);
	if (lsauto)
	{
		tmp = *lsauto;
		tmp2 = tmp;
		while (tmp2)
		{
			tmp2 = tmp->next;
			free(tmp->value);
			free(tmp);
			tmp = tmp2;
		}
	}
}
