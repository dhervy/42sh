/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs.utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:52:27 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/07 16:52:48 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**tab_extract(char **tb, int i)
{
	char	**t;
	int		c;

	c = -1;
	t = malloc(sizeof(char*) * tab_size(tb));
	while (tb[++c] && c < i)
		t[c] = ft_strdup(tb[c]);
	while (tb[++c])
		t[c - 1] = ft_strdup(tb[c]);
	t[c - 1] = 0;
	tab_free(tb);
	return (t);
}

char	**tab_inject(char **tb, int i, char *str)
{
	char	**t;
	int		c;

	c = -1;
	t = malloc(sizeof(char*) * (tab_size(tb) + 2));
	while (tb && tb[++c] && c < i)
		t[c] = ft_strdup(tb[c]);
	t[c++] = ft_strdup(str);
	while (tb && tb[c - 1])
	{
		t[c] = ft_strdup(tb[c - 1]);
		c++;
	}
	t[c] = 0;
	tb ? tab_free(tb) : 0;
	return (t);
}

char	**tab_add(char **tb, char *str)
{
	char	**t;
	int		c;

	c = -1;
	t = malloc(sizeof(char*) *
	((tb ? tab_size(tb) : 0) + 2));
	while (tb && tb[++c])
		t[c] = ft_strdup(tb[c]);
	t[!tb ? 0 : c++] = ft_strdup(str);
	t[!tb ? 1 : c] = 0;
	tb ? tab_free(tb) : 0;
	return (t);
}
