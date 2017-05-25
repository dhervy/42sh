/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.dquotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 15:12:59 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 00:56:08 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	test_quotes2(char *s, int *i, int *tt, int *d)
{
	if (s[*i] == '\\' && nescape(s, *i))
	{
		*tt = 3;
		*d = 0;
		if (!s[*i + 1])
		{
			*d = 1;
			(*i)++;
		}
	}
}

void	test_quotes(char *s, int *i, int *tt, int *d)
{
	if (s[*i] == '\"' && nescape(s, *i))
	{
		*tt = 1;
		*d = 1;
		while (s[++(*i)])
			if (s[*i] == '\"' && nescape(s, *i))
				break ;
		s[*i] && s[*i] == '\"' ? *d = 0 : 0;
	}
	else if (s[*i] == '\'' && nescape(s, *i))
	{
		*tt = 2;
		*d = 1;
		while (s[++(*i)])
			if (s[*i] == '\'' && nescape(s, *i))
				break ;
		s[*i] && s[*i] == '\'' ? *d = 0 : 0;
	}
	else
		test_quotes2(s, i, tt, d);
}

char	*replace_dloop(t_me *me, char **qtype, char *s, int tt)
{
	init_term(me);
	if (tt == 3)
	{
		*qtype = ft_strdup("\\");
		if (s)
			s[ft_strlen(s) - 1] = 0;
	}
	else
		*qtype = ft_strdup(tt == 1 ? "\"" : "\'");
	if (!(s = join_free(s, dquote_gnl(me, qtype))))
	{
		*qtype ? free(*qtype) : 0;
		exit_term(me);
		return (0);
	}
	else
	{
		*qtype ? free(*qtype) : 0;
		exit_term(me);
		return (s);
	}
}

char	*check_dquotes(t_me *me, char *s)
{
	int		d;
	int		i;
	char	*tmp;
	char	*qtype;
	int		tt;

	i = -1;
	d = 0;
	qtype = 0;
	if (s)
	{
		while (s[++i])
		{
			tmp = 0;
			d = 0;
			tt = 0;
			if (nescape(s, i))
				test_quotes(s, &i, &tt, &d);
			if (d && !s[i])
				return (replace_dloop(me, &qtype, s, tt));
		}
	}
	return (s);
}
