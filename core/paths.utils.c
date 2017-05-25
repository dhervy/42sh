/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 11:39:34 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/06 10:34:52 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*fpath(char *path, char *dir)
{
	char *tmp;
	char *r;

	tmp = ft_strjoin("/", dir);
	r = ft_strjoin(path, tmp);
	free(tmp);
	return (r);
}

char	*exec_check(char *name)
{
	char		*r;
	struct stat	s;

	r = 0;
	if (!stat(name, &s) && s.st_mode & S_IXUSR)
		if (!access(name, F_OK) && !access(name, X_OK))
			r = ft_strdup(name);
	return (r);
}

void	get_path_core(char **t, int *i, char **r, char *name)
{
	char *p;

	while (t[++(*i)] && (p = fpath(t[(*i)], name)))
	{
		if ((*r) && !access(p, F_OK))
		{
			free(*r);
			*r = 0;
		}
		*r = !access(p, F_OK) ? ft_strdup(p) : *r;
		free(p);
	}
}

char	*get_path(t_me *me, char *name)
{
	char	*p;
	char	**t;
	char	*r;
	int		i;

	i = -1;
	r = 0;
	if (!(p = get_edt(me->e, "PATH")))
		return (exec_check(name));
	t = ft_strsplit(p, ':');
	free(p);
	get_path_core(t, &i, &r, name);
	tab_free(t);
	if (!r)
		r = exec_check(name);
	return (r);
}
