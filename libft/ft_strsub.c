/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:50:48 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 14:16:05 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char	*ne;
	size_t	a;

	a = 0;
	if (!s || ((start + len) > ft_strlen(s)))
		return (NULL);
	if (!(ne = ft_strnew(len + 1)))
		return (NULL);
	while (a < len && s[start + a])
	{
		ne[a] = s[start + a];
		a++;
	}
	ne[a] = 0;
	return (ne);
}
