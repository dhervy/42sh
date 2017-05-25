/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 12:12:11 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 14:15:38 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ne;
	unsigned int	len;

	len = 0;
	while (s[len])
		len++;
	ne = (char *)malloc((len + 1) * sizeof(char));
	if (!ne)
		return (NULL);
	len = 0;
	while (s[len])
	{
		ne[len] = f(len, s[len]);
		len++;
	}
	ne[len] = '\0';
	return (ne);
}
