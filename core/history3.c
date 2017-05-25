/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertojo <tbertojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 02:23:51 by tbertojo          #+#    #+#             */
/*   Updated: 2017/05/03 02:35:22 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	affi_history(t_me *me, int r, int fd, int affindex)
{
	t_hist	*tmp;
	int		i;

	find_index_max(me, &i);
	tmp = me->hi;
	while (tmp)
	{
		if (r)
		{
			if (affindex)
				affi_hist_index(tmp, i, fd);
			if ((!affindex && !tmp->inlist) || (affindex))
			{
				ft_putendl_fd(tmp->name, fd);
				if (!affindex)
					tmp->inlist = 1;
			}
			r = r > 0 ? r - 1 : r;
		}
		tmp = tmp->next;
	}
}

int		usage_history(void)
{
	ft_putendl("42sh : history: -d: option requires an argument");
	ft_putendl("history: usage: history [-c] [-d offset] [n] or history -awrn \
	[filename] or history -ps arg [arg...]");
	return (0);
}

int		is_c(char **tabb)
{
	int i;
	int s;
	int t;

	s = 0;
	t = -1;
	i = 0;
	while (tabb[++t] && tabb[t][i] && tabb[t][i] == '-')
	{
		while (tabb[t][i])
		{
			if (tabb[t][i] == 'c' && i == 1 && !tabb[t][i + 1])
				return (1);
			else if (tabb[t][i] == 'c')
				return (usage_history());
			else if (tabb[t][i] == '-' && tabb[t][i + 1] &&\
			tabb[t][i + 1] >= '0' && tabb[t][i + 1] <= '9')
				return (2);
			i++;
		}
		i = 0;
	}
	return (0);
}

void	rm_list_elem(t_me *me, t_hist *tmp, int *i)
{
	t_hist	*prev;
	t_hist	*tmp2;

	*i = !tmp->prev ? 2 : *i;
	tmp2 = tmp->next;
	prev = tmp->prev;
	free(tmp->name);
	free(tmp);
	tmp = tmp2;
	if (*i == 2)
	{
		tmp->prev = NULL;
		me->hi = tmp;
	}
	else if (tmp)
	{
		tmp->prev = prev;
		prev->next = tmp;
	}
	else
		prev->next = NULL;
	*i = 1;
}

void	rm_history(t_me *me, int nb)
{
	t_hist	*tmp;
	int		i;

	i = 0;
	tmp = me->hi;
	if (tmp && !tmp->next)
	{
		free(tmp->name);
		free(tmp);
		me->hi = NULL;
		return ;
	}
	while (tmp)
	{
		if (tmp->index + 1 == nb && i == 0 && tmp && tmp->name)
			rm_list_elem(me, tmp, &i);
		if (i == 1 && tmp)
			tmp->index = tmp->index - 1;
		tmp = tmp->next;
	}
}
