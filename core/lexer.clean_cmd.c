/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.clean_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 14:22:39 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/02 22:24:34 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		nescape(char *s, int i)
{
	int		r;

	if (!s || i < 1)
		return (1);
	r = s[i - 1] != '\\' ? 1 : 0;
	if (!r && i > 1)
		r = s[i - 2] == '\\' ? 1 : 0;
	return (r);
}

int		char_isnot(char c, char *s, int i)
{
	if (!s || i < 0)
		return (0);
	if (s[(i)] != c ||
		(s[(i)] == c && !nescape((char*)s, i)))
		return (1);
	return (0);
}

void	clean_cmd_data2(char **t, int i)
{
	int		c;
	char	type;

	while (t[i])
	{
		c = -1;
		while (t[i][++c])
		{
			if (nescape(t[i], c) &&
			(t[i][c] == '\"' || t[i][c] == '\''))
			{
				type = t[i][c++];
				while (t[i][c] && t[i][c] != type)
					++c;
			}
			if (t[i][c] == '\\')
				t[i] = string_del(t[i], c);
		}
		++i;
	}
}

void	clean_data_quotes(char **str, int *i, char ***t)
{
	char	type;
	char	*tmp;

	if (nescape(*str, *i) &&
	((*str)[*i] == '\"' || (*str)[*i] == '\''))
	{
		type = (*str)[*i];
		tmp = ft_itoa(*i);
		*t = tab_add(*t, tmp);
		tmp ? free(tmp) : 0;
		(*i)++;
		while ((*str)[*i] && (*str)[*i] != type)
			++(*i);
		if ((*str)[*i] && (*str)[*i] == type)
		{
			tmp = ft_itoa(*i);
			*t = tab_add(*t, tmp);
			tmp ? free(tmp) : 0;
		}
	}
}

void	clean_cmd_data(char **t, int i)
{
	int		c;
	char	**del;

	--i;
	while (t[++i] && !get_token(t[i]))
	{
		c = -1;
		del = 0;
		while (t[i][++c])
			clean_data_quotes(&(t[i]), &c, &del);
		c = -1;
		while (del && del[++c])
			t[i] = string_del(t[i], ft_atoi(del[c]) - c);
		del ? tab_free(del) : 0;
	}
}
