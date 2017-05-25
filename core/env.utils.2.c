/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.utils.2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 11:31:44 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/06 10:34:27 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		start_by(char *s, char *start)
{
	int		a;

	a = -1;
	while (start[++a] && s[a])
		if (s[a] != start[a])
			return (0);
	return (1);
}

char	*get_first(char *s)
{
	int		a;

	a = ft_strlen(s);
	while (s[--a] && s[a] != '/')
		;
	return (s[a] ? ft_strndup(s, a) : 0);
}

int		env_isin(char **e, char *s)
{
	int	a;

	a = -1;
	if (!e || !*e)
		return (0);
	while (e[++a])
		if (start_by(s, e[a]))
			return (1);
	return (0);
}

void	print_env(char **e)
{
	int	a;

	a = -1;
	while (e[++a])
		ft_putendl(e[a]);
}

char	*env_to_s(char **e)
{
	int		a;
	char	*s;
	char	*t;
	char	*p;

	a = -1;
	s = ft_strnew(1);
	while (e[++a])
	{
		p = ft_strjoin(" ", e[a]);
		t = s;
		s = ft_strjoin(s, p);
		free(t);
		free(p);
	}
	return (s);
}
