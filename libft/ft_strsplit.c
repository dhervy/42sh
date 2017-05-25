/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:45:18 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 15:50:42 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		count_w(char const *s, char c)
{
	int		i;
	int		nw;

	nw = 0;
	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] != c)
			{
				nw++;
				while (s[i] && s[i] != c)
					i++;
			}
			else
				i++;
		}
		return (nw);
	}
	return (0);
}

static int		pass_deli(char const *s, int i, char c)
{
	if (s)
	{
		while (s[i] && s[i] == c)
			i++;
		return (i);
	}
	return (0);
}

static int		count_size(char const *str, int i, char c)
{
	int size;

	size = 0;
	if (str)
	{
		while (str[i] != c && str[i])
		{
			size++;
			i++;
		}
		size++;
		return (size);
	}
	return (0);
}

char			**ft_strsplit(const char *s, char c)
{
	int		w;
	char	**tab;
	int		a;
	int		n;
	int		i;

	a = pass_deli(s, 0, c);
	n = 0;
	w = count_w(s, c);
	if (!s || !(tab = malloc(sizeof(char*) * w + 1)))
		return (0);
	while (s[a] && n < w)
	{
		i = 0;
		if (!(tab[n] = (char*)malloc(count_size(s, a, c))))
			return (NULL);
		while (s[a] != c && s[a])
			tab[n][i++] = s[a++];
		tab[n++][i] = 0;
		a++;
		while (s[a] == c && s[a])
			a++;
	}
	tab[n] = NULL;
	return (tab);
}
