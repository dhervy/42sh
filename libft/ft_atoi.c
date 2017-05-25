/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 14:08:10 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 14:11:00 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	nb;
	int	i;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	if (str[i])
	{
		while (str[i] == ' ' || (str[i] <= '\r' && str[i] > '\b'))
			i++;
		if (str[i] == '+' || str[i] == '-')
			sign = (str[i++] == '-') ? -1 : 1;
		while (str[i] && ft_isdigit(str[i]))
			nb = (nb * 10) + (str[i++] - '0');
	}
	return (nb * sign);
}
