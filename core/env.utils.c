/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 11:33:16 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/12 16:03:34 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		env_n(char **e)
{
	int	i;

	i = -1;
	if (!e || !*e)
		return (0);
	while (e[++i])
		;
	return (i);
}

char	**env_add(char **e, char *name, char *value)
{
	int		a;
	char	**n;
	char	*s;
	char	*t;
	int		f;

	a = 0;
	f = e && *e ? 1 : 0;
	s = ft_strjoin(name, "=");
	t = s;
	s = ft_strjoin(s, value);
	free(t);
	n = malloc(sizeof(char*) * (env_n(e) + 2));
	while (e && *e && e[a])
	{
		n[a] = ft_strdup(e[a]);
		a++;
	}
	n[a] = s;
	n[a + 1] = NULL;
	f ? tab_free(e) : 0;
	return (n);
}

char	**env_sub(char **e, char *name)
{
	int		a;
	int		b;
	char	**n;
	char	*s;

	a = -1;
	b = -1;
	if (!(s = ft_strjoin(name, "=")))
		return (e);
	if (!env_isin(e, s))
	{
		ft_putstr_fd("Unable to unset key \"", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd("\"", 2);
		free(s);
		return (e);
	}
	n = malloc(sizeof(char*) * (env_n(e)));
	while (e[++a])
		if (!start_by(e[a], s))
			n[++b] = ft_strdup(e[a]);
	n[b + 1] = NULL;
	tab_free(e);
	s ? free(s) : 0;
	return (n);
}

char	**env_modif(char **e, char *name, char *value)
{
	int		a;
	char	**at;
	char	*new;
	char	*ts;

	a = -1;
	if (!name || !value)
		return (0);
	ts = ft_strjoin(name, "=");
	while (e[++a])
	{
		if (start_by(ts, e[a]))
		{
			at = &(e[a]);
			new = ft_strjoin(ts, value);
			*at ? free(*at) : 0;
			*at = new;
		}
	}
	free(ts);
	return (e);
}

char	*get_edt(char **e, char *data)
{
	int		a;
	char	*at;
	char	*ts;
	char	*r;

	a = -1;
	if (!e || !data)
		return (0);
	while (e[++a] && !(ts = 0))
	{
		ts = ft_strjoin(data, "=");
		if ((at = ft_strstr(e[a], ts)))
		{
			if (at + 1 + ft_strlen(ts))
			{
				r = ft_strdup(at + ft_strlen(ts));
				free(ts);
				return (r);
			}
		}
		else
			free(ts);
	}
	return (0);
}
