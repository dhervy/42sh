/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 12:23:06 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 14:15:34 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	i_src;
	size_t	i_dst;

	len_dst = ft_strlen(dst);
	i_dst = len_dst;
	i_src = 0;
	if (size < len_dst)
		return (size + ft_strlen(src));
	while (i_dst < (size - 1) && src[i_src])
		dst[i_dst++] = src[i_src++];
	dst[i_dst] = '\0';
	return (ft_strlen(src) + len_dst);
}
