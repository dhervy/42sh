/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:50:37 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/31 15:46:53 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		isin_squote(char *s, int i)
{
	int		c;
	int		io;

	c = -1;
	io = 1;
	while (s[++c] && c < i)
	{
		if (s[i] == '\'')
			io *= -1;
	}
	return (io > 0 ? 0 : 1);
}

char	*clean_equot(char *s)
{
	char *a;

	if (!s || !*s)
		return (0);
	if (*s == '\"')
	{
		a = ft_strdup(&(s[1]));
		free(s);
		s = a;
	}
	if (s[ft_strlen(s)] == '\"')
	{
		a = ft_strndup(s, ft_strlen(s));
		free(s);
		s = a;
	}
	return (s);
}

char	*join_free(char *a, char *b)
{
	char *r;

	r = ft_strjoin(a, b);
	if (a)
		free(a);
	if (b)
		free(b);
	return (r);
}

char	*string_del(char *r, int i)
{
	char	*new;
	int		c;

	if (!(new = malloc(sizeof(char) * (ft_strlen(r)))))
		return (r);
	c = -1;
	while (r[++c] && c < i)
		new[c] = r[c];
	++c;
	while (r[c])
	{
		new[c - 1] = r[c];
		++c;
	}
	new[c - 1] = 0;
	free(r);
	return (new);
}

char	*string_inject(char *r, char *n, int i, int replace)
{
	char	*new;
	int		c;
	int		d;

	if (!r || !n)
		return (0);
	new = malloc(ft_strlen(r) + ft_strlen(n));
	c = -1;
	while (r[++c] && c < i)
		new[c] = r[c];
	d = -1;
	while (n[++d])
		new[c + d] = n[d];
	replace ? --d : 0;
	while (r[++c])
		new[c + d] = r[c];
	new[c + d] = 0;
	free(r);
	return (new);
}
