/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   afd.load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 14:10:36 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/05 14:56:11 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	get_rest(char *s, t_afd *ma)
{
	ma->type = *s == '>' && *(s + 1) == '>' ? ADD : NONE;
	*s == '>' && *(s + 1) != '>' ? ma->type = OVER : 0;
	*s == '<' ? ma->type = CLOSE : 0;
	s += (ma->type == ADD ? 2 : 1);
	ma->i_file = *s == '&' ? 0 : 1;
	!ma->i_file ? ++s : 0;
	if (!ma->i_file && *s == '-' && !(ma->i_file = 0))
		ma->type = CLOSE;
	else if (ma->i_file)
		ma->file_name = ft_strdup(s);
	else
		ma->new = ft_atoi(s);
}

t_afd	*create_afd(char *s)
{
	t_afd	*ma;

	if (!s)
		return (0);
	ma = malloc(sizeof(t_afd));
	ma->str = ft_strdup(s);
	ma->next = 0;
	ma->new = -1;
	ma->old = -1;
	ma->file_name = 0;
	if (*s == '&' && (++s))
		ma->special = '&';
	ma->old = *s == '>' ? 1 : ft_atoi(s);
	*s == '<' ? ma->old = 0 : 0;
	while (ft_isdigit(*s))
		++s;
	get_rest(s, ma);
	return (ma);
}

t_afd	*push_afd(t_afd *begin, char *str)
{
	t_afd	*new;
	t_afd	*curs;

	if (!(new = create_afd(str)))
		return (0);
	curs = begin;
	if (!curs)
		begin = new;
	else
	{
		while (curs->next)
			curs = curs->next;
		curs->next = new;
	}
	return (begin);
}

t_afd	*create_afd_list(char **afd)
{
	t_afd *list;

	list = 0;
	if (!afd)
		return (0);
	while (afd && *afd)
	{
		list = push_afd(list, *afd);
		++afd;
	}
	return (list);
}

char	**get_afds(t_me *me, char **s)
{
	int		i;
	char	*tmp[2];

	i = -1;
	me->afds = 0;
	while (s[++i])
	{
		if (is_afd(s[i]) || !ft_strcmp(s[i], ";") ||
		!ft_strcmp(s[i], "&&") || !ft_strcmp(s[i], "||"))
		{
			tmp[1] = me->afds;
			tmp[0] = ft_strjoin(s[i], " ");
			me->afds = ft_strjoin(me->afds, tmp[0]);
			tmp[1] ? free(tmp[1]) : 0;
			free(tmp[0]);
			if (ft_strcmp(s[i], ";") && ft_strcmp(s[i], "&&") &&
			ft_strcmp(s[i], "||"))
				s = tab_extract(s, i--);
		}
		if (!s[i])
			break ;
	}
	me->afd = me->afds ? ft_strsplit(me->afds, ' ') : 0;
	free(me->afds);
	return (s);
}
