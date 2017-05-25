/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.p_ex2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertojo <tbertojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 02:36:55 by tbertojo          #+#    #+#             */
/*   Updated: 2017/05/03 02:41:54 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		rm_last_elem_hist2(t_me *me, t_hist *tmp)
{
	if (tmp && tmp->name)
		free(tmp->name);
	if (tmp)
		free(tmp);
	me->hi = NULL;
	return (1);
}

void	rm_last_elem_hist(t_me *me)
{
	t_hist	*tmp;
	t_hist	*tmp2;

	tmp2 = NULL;
	tmp = me->hi;
	if (tmp)
	{
		while (tmp->next && tmp->next->next)
			tmp = tmp->next;
		if (!tmp->next && rm_last_elem_hist2(me, tmp))
			return ;
		tmp = tmp->next;
		if (tmp && tmp->prev)
			tmp2 = tmp->prev;
		if (tmp && tmp->name)
			free(tmp->name);
		if (tmp)
			free(tmp);
		if (tmp2)
			tmp2->next = NULL;
		else
			me->hi = NULL;
	}
	else
		ft_putendl("42sh : event not fond.");
}

char	*last_elem_hist(t_me *me)
{
	t_hist	*tmp;
	char	*line;

	line = NULL;
	tmp = me->hi;
	if (tmp)
	{
		while (tmp->next && tmp->next->next)
			tmp = tmp->next;
		line = ft_strdup(tmp->name);
	}
	else
		ft_putendl("42sh : event not fond.");
	return (line);
}

char	*find_param(t_me *me, char *str)
{
	char	*line;
	char	*tmp;
	int		i;

	tmp = NULL;
	i = -1;
	if (str == NULL && (line = last_elem_hist(me)) == NULL)
		return (NULL);
	line = str ? str : line;
	while (line[i + 1] && line[++i] != ' ')
		;
	tmp = ft_strdup(&line[i + 1]);
	free(line);
	return (tmp);
}

char	*n_elem_hist_find_end(char *line, char *tmp, int i)
{
	char	*tmp2;

	tmp = NULL;
	tmp = ft_strdup(&line[i]);
	i = 0;
	while (tmp && tmp[i] && tmp[i] != ' ')
		i++;
	if (tmp)
	{
		tmp2 = ft_strndup(tmp, i);
		free(tmp);
		tmp = tmp2;
	}
	return (tmp);
}
