/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 13:17:03 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 13:57:29 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	int		i;
	size_t	c;

	c = 0;
	if (!*s2)
		return ((char*)s1);
	while (s1[c] && c < n)
	{
		if (s1[c] == s2[0] && !(i = 0))
			while (s1[c + i] == s2[i] && s1[c + i] && (c + i) < n)
			{
				i++;
				if (!s2[i])
					return ((char*)s1 + c);
			}
		c++;
	}
	return (0);
}
