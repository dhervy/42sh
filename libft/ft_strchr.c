/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:41:57 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 14:15:19 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		l;
	char	ch;

	i = 0;
	ch = (char)c;
	l = ft_strlen(s);
	if (!ch || !c)
		return ((char*)s + l);
	while (i <= l)
	{
		if (s[i] == (char)c)
			return ((char*)s + i);
		i++;
	}
	return (0);
}
