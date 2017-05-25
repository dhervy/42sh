/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:06:46 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 14:14:04 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*sr;
	unsigned char		*ds;

	sr = (const unsigned char*)src;
	ds = (unsigned char*)dst;
	while (n--)
		*ds++ = *sr++;
	return (dst);
}
