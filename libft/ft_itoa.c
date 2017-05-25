/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:45:34 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 14:20:27 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		get_int_len(int n)
{
	int	s;

	s = 0;
	if (!n)
		return (1);
	if (n < 0)
		s++;
	while (n /= 10)
		s++;
	s++;
	return (s);
}

char			*ft_itoa(int n)
{
	char	*ne;
	int		len_n;
	int		neg;

	if (n == -2147483648)
		return ("-2147483648");
	len_n = get_int_len(n);
	ne = ft_strnew(len_n + 1);
	neg = 0;
	if (!ne)
		return (NULL);
	if (n < 0)
	{
		neg = 1;
		ne[0] = '-';
		n *= -1;
	}
	while (len_n-- > neg)
	{
		ne[len_n] = n % 10 + '0';
		n /= 10;
	}
	return (ne);
}
