/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 13:58:32 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/01 12:24:40 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char	*ne;

	if (!s1)
		return (0);
	ne = ft_strnew((int)ft_strlen(s1) + 1);
	if (!ne)
		return (NULL);
	ft_strcpy(ne, s1);
	return (ne);
}
