/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.p_ex3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertojo <tbertojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 02:48:19 by tbertojo          #+#    #+#             */
/*   Updated: 2017/05/03 02:48:57 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*n_elem_hist(t_me *me, int num_param, char *str)
{
	char	*line;
	t_hist	*hist;
	char	*tmp;
	int		i;
	int		nb;

	i = -1;
	nb = 0;
	tmp = NULL;
	hist = me->hi;
	while (str == NULL && hist && hist->next && hist->next->next)
		hist = hist->next;
	line = str ? str : ft_strdup(hist->name);
	while (line[i + 1] && line[++i] && nb < num_param)
		if (line[i] == ' ')
			nb++;
	if (!line[i + 1])
	{
		free(line);
		return (NULL);
	}
	tmp = n_elem_hist_find_end(line, tmp, i);
	free(line);
	return (tmp);
}

char	*find_last_param(t_me *me, char *str)
{
	char	*line;
	char	*tmp;
	int		i;

	tmp = NULL;
	if (str == NULL && (line = last_elem_hist(me)) == NULL)
		return (NULL);
	line = str ? str : line;
	i = ft_strlen(line);
	while (line[i - 1] && line[--i] != ' ')
		;
	tmp = ft_strdup(&line[i]);
	free(line);
	return (tmp);
}

void	find_cmp(char **fin, char **file, char *str)
{
	int		i;
	char	*test;

	i = 0;
	test = NULL;
	*fin = NULL;
	*file = NULL;
	while (str[i] && str[i] != ' ')
	{
		if (!(*file))
			*file = ft_strndup(&str[i], 1);
		else
		{
			test = ft_strndup(&str[i], 1);
			*file = ft_strjoinfree(*file, test, 3);
		}
		i++;
	}
	*fin = ft_strdup(&str[i]);
}

void	find_cmp_option(int *t, int *nb, char **file, int r)
{
	char	*tmp2;

	*nb = 0;
	tmp2 = NULL;
	while ((*file)[++r])
		if ((*file)[r] == ':')
		{
			if ((*file)[r + 1] && (*file)[r + 1] == '$' && (!(*file)[r + 2] || \
			(*file)[r + 2] == ' '))
				*t = 1;
			else if ((*file)[r + 1] && (*file)[r + 1] == '*' && \
			(!(*file)[r + 2] || (*file)[r + 2] == ' '))
				*t = 2;
			else if ((*file)[r + 1] && (*file)[r + 1] != ' ')
			{
				*t = 3;
				*nb = ft_atoi(&(*file)[r + 1]);
			}
			if (t)
			{
				tmp2 = ft_strndup(*file, r);
				free(*file);
				*file = tmp2;
			}
		}
}

char	*find_same_hist_return2(t_me *me, t_hist *tmp, char *fin, int nb)
{
	char	*tmp2;

	tmp2 = NULL;
	tmp2 = n_elem_hist(me, nb, ft_strdup(tmp->name));
	if (tmp2)
		return (ft_strjoinfree(tmp2, fin, 3));
	free(fin);
	return (NULL);
}
