/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:43:01 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 14:15:41 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char		*p1;
	const unsigned char		*p2;
	size_t					i;

	i = 0;
	p1 = (unsigned char*)s1;
	p2 = (unsigned char*)s2;
	if (!n || (!*s1 && !*s2))
		return (0);
	while (i < n && p1[i] == p2[i] && p1[i])
		i++;
	if (i < n || (i >= n && p1[i] == p2[i]))
		return (p1[i] - p2[i]);
	return (0);
}
