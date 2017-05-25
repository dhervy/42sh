/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:08:49 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 15:43:28 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			is_blank(char c)
{
	if (c == '\n' || c == '\t' || c == ' ')
		return (1);
	return (0);
}

static int			getlen(const char *s)
{
	int				i;
	int				len;

	i = 0;
	len = (int)ft_strlen(s);
	while (s[i] && is_blank(s[i]))
	{
		i++;
		len--;
	}
	i = (int)ft_strlen(s) - 1;
	while (s[i] && is_blank(s[i]))
	{
		i--;
		len--;
	}
	return (len);
}

char				*ft_strtrim(char const *s)
{
	char			*newstr;
	int				len;
	int				i;
	int				j;

	if (!(i = 0) && !s)
		return (NULL);
	if (!is_blank(s[0]) && !is_blank(s[ft_strlen(s) - 1]))
		return (ft_strdup(s));
	len = getlen(s);
	while (s[i] && is_blank(s[i]))
		i++;
	if (!s[i])
		return ("");
	if (!(newstr = malloc(len + 1)))
		return (NULL);
	j = i;
	i = 0;
	while (i < len && s[i + j])
	{
		newstr[i] = s[i + j];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
