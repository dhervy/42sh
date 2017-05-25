/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 13:58:32 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/06 14:13:06 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s1, int n)
{
	char	*ne;
	int		a;

	a = -1;
	ne = (char*)malloc(n + 1);
	if (!ne || !s1)
		return (NULL);
	n > (int)ft_strlen(s1) ? n = ft_strlen(s1) : 0;
	n < 0 ? n = 0 : 0;
	while (s1[++a] && a < n)
		ne[a] = s1[a];
	ne[a] = 0;
	return (ne);
}
