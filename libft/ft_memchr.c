/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:06:46 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 14:13:58 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*ptr;
	size_t					i;

	ptr = ((const unsigned char*)s);
	i = 0;
	if (i >= n)
		return (NULL);
	while (n--)
	{
		if (ptr[i] == (unsigned char)c)
			return (void*)(ptr + i);
		i++;
	}
	return (NULL);
}
