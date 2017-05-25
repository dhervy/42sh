/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.var_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:14:22 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/31 15:41:28 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		init_rbv(char *s, int *dollar, int *i)
{
	if (!s)
		return (0);
	*dollar = s[*i] && s[*i] == '$' ? 1 : 0;
	if (s[*i] && s[*i] == '$')
		++(*i);
	if (!s[*i])
		return (0);
	return (1);
}

void	init_rbv_tab(char **in, char *s, int i, int dollar)
{
	in = tab_nset(in, 3);
	in[0] = ft_strndup(s, i - (dollar ? 1 : 0));
	in[1] = ft_strndup(&(s[i]), var_name_size(&(s[i])));
	in[2] = ft_strdup(&s[i + var_name_size(&(s[i]))]);
}

char	*replace_by_value(t_me *me, char *s, int i)
{
	int		dollar;
	char	**in;
	char	*r;
	char	*tmp;

	if (!init_rbv(s, &dollar, &i))
		return (0);
	in = malloc(sizeof(char*) * 5);
	init_rbv_tab(in, s, i, dollar);
	if (me->alias && !dollar)
		in[3] = get_edt(me->alias, in[1]);
	else if (me->e && dollar)
		in[3] = get_edt(me->e, in[1]);
	in[4] = 0;
	if (in[3])
	{
		tmp = ft_strjoin(in[0], in[3]);
		r = ft_strjoin(tmp, in[2]);
		free(tmp);
		tab_nfree(in, 3);
		return (r);
	}
	tab_nfree(in, 3);
	return (0);
}

int		replace_variables_core(t_me *me, char **s, int *i)
{
	char	*tmp;
	int		hquote;

	hquote = 0;
	while ((*s)[(*i)] && (*s)[(*i)] == ' ')
		++(*i);
	if (!(*s) || !(*s)[(*i)])
		return (0);
	if (var_name_size(&((*s)[(*i)])) >= 1)
	{
		if ((*s)[(*i)] == '\"' && ++(*i))
			hquote = 1;
		if ((tmp = replace_by_value(me, (*s), (*i))))
		{
			free((*s));
			tmp = hquote ? join_free(tmp, ft_strdup("\"")) : tmp;
			(*s) = tmp;
			(*i) = -1;
		}
		while ((*s)[(*i)] && (*s)[(*i)] != ' ')
			++(*i);
	}
	return (1);
}

char	*replace_variables(t_me *me, char *s)
{
	int		i;

	if (!me || (!me->e))
		return (0);
	i = -1;
	while (s[++i])
	{
		if (!(replace_variables_core(me, &s, &i)))
			return (0);
		if (i > -1 && !s[i])
			return (s);
	}
	return (s);
}
