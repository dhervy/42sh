/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:16:53 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 14:14:07 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*swap;

	swap = (void*)malloc(len);
	if (swap)
	{
		ft_memcpy(swap, src, len);
		ft_memcpy(dst, swap, len);
		free(swap);
		return (dst);
	}
	return (NULL);
}
