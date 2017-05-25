/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 12:12:11 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 14:15:37 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ne;
	int		len;

	len = 0;
	while (s[len])
		len++;
	ne = malloc((len + 1) * sizeof(char));
	if (!ne || !s)
		return (NULL);
	len = 0;
	while (s[len])
	{
		ne[len] = f(s[len]);
		len++;
	}
	ne[len] = '\0';
	return (ne);
}
