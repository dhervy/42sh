/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:19:22 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/04 15:41:51 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static	void	count_w_core(const char *s, int *i, int *nw)
{
	if (s[(*i)] != ' ')
	{
		(*nw)++;
		while (s[(*i)] && char_isnot(' ', (char*)s, *i))
		{
			if (nescape((char*)s, *i) && s[(*i)] == '\"' && ++(*i))
				while (s[(*i)] && s[(*i)] != '\"')
					++(*i);
			else if (nescape((char*)s, *i) && s[(*i)] == '\'' && ++(*i))
				while (s[(*i)] && s[(*i)] != '\'')
					++(*i);
			(*i)++;
		}
	}
	else
		(*i)++;
}

static	int		count_w(char const *s, char c)
{
	int		i;
	int		nw;

	(void)c;
	nw = 0;
	i = 0;
	if (s)
	{
		while (s[i])
			count_w_core(s, &i, &nw);
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

void			msplit_core(char **tabo, char *s, int *a, int *n)
{
	int		i;

	i = 0;
	while (s[(*a)] && char_isnot(' ', s, *a))
	{
		if (!nescape(s, *a) || (s[(*a)] != '\"' && s[(*a)] != '\''))
			tabo[(*n)][i++] = s[(*a)++];
		if (s[(*a)] == '\"' && nescape(s, *a))
		{
			tabo[(*n)][i++] = s[(*a)++];
			while (s[(*a)] && s[*a] != '\"')
				tabo[(*n)][i++] = s[(*a)++];
			tabo[(*n)][i++] = s[(*a)++];
		}
		if (s[(*a)] == '\'' && nescape(s, *a))
		{
			tabo[(*n)][i++] = s[(*a)++];
			while (s[(*a)] && s[*a] != '\'')
				tabo[(*n)][i++] = s[(*a)++];
			tabo[(*n)][i++] = s[(*a)++];
		}
	}
	tabo[(*n)++][i] = 0;
}

char			**msplit(char *s, char c)
{
	int		w;
	char	**tabo;
	int		a;
	int		n;
	int		i;

	a = pass_deli(s, 0, c);
	n = 0;
	w = count_w(s, c);
	if (!s || !(tabo = malloc(sizeof(char*) * (w + 1))))
		return (0);
	while (s[a] != 0 && n < w)
	{
		i = 0;
		if (!(tabo[n] = (char*)malloc(count_size(s, a, c))))
			return (NULL);
		msplit_core(tabo, s, &a, &n);
		a++;
		while (s[a] && s[a] == c)
			a++;
	}
	tabo[n] = NULL;
	return (tabo);
}
