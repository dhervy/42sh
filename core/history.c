/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertojo <tbertojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 22:05:45 by tbertojo          #+#    #+#             */
/*   Updated: 2017/05/03 02:27:22 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	history_s2(t_hist *tmp, t_me *me, char **str)
{
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		if (tmp->name)
			free(tmp->name);
		tmp->name = *str;
	}
	else
	{
		push_hist(me, *str);
		free(*str);
	}
}

void	history_s(t_me *me, char **tabb)
{
	int		i;
	char	*str;
	t_hist	*tmp;

	i = -1;
	str = NULL;
	while (tabb[++i])
	{
		if (!str)
			str = ft_strdup(tabb[i]);
		else
		{
			str = ft_strjoinfree(str, " ", 1);
			str = ft_strjoinfree(str, tabb[i], 1);
		}
	}
	tmp = me->hi;
	history_s2(tmp, me, &str);
}

void	history_p(t_me *me, char **tabb)
{
	int		i;
	t_hist	*tmp;
	t_hist	*tmp2;

	i = -1;
	tmp2 = NULL;
	while (tabb[++i])
		ft_putendl(tabb[i]);
	tmp = me->hi;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		if (tmp->prev)
			tmp2 = tmp->prev;
		if (tmp->name)
			free(tmp->name);
		free(tmp);
		if (tmp2)
			tmp2->next = NULL;
		else
			me->hi = NULL;
	}
}

void	history(t_me *me, t_node *curs)
{
	int res;

	res = is_c(&curs->cmd->args[1]);
	if (curs->cmd->args && !curs->cmd->args[1])
		affi_history(me, -1, 1, 1);
	else if (curs->cmd->args && curs->cmd->args[1] &&\
		curs->cmd->args[1][0] == '-' &&\
		res == 1)
		clean_history(me);
	else if (curs->cmd->args && curs->cmd->args[1] &&\
		curs->cmd->args[1][0] != '-')
		affi_end_history(me, ft_atoi(curs->cmd->args[1]), 1, 1);
	else if (curs->cmd->args && curs->cmd->args[1] &&\
		curs->cmd->args[1][0] == '-' && \
		curs->cmd->args[1][1] == 's' && curs->cmd->args[2])
		history_s(me, &curs->cmd->args[2]);
	else if (curs->cmd->args && curs->cmd->args[1] &&\
		curs->cmd->args[1][0] == '-' && \
		curs->cmd->args[1][1] == 'p' && curs->cmd->args[2])
		history_p(me, &curs->cmd->args[2]);
	else
		history_2(me, curs, res);
}

void	history_2(t_me *me, t_node *curs, int res)
{
	(void)res;
	if (curs->cmd->args && curs->cmd->args[1] &&\
		curs->cmd->args[1][0] == '-' && \
		curs->cmd->args[1][1] == 'r')
		curs->cmd->args[2] ? history_r(me, curs->cmd->args[2], 0) :\
		history_r(me, find_hist_file(me), 1);
	else if (curs->cmd->args && curs->cmd->args[1] &&\
		curs->cmd->args[1][0] == '-' && \
		curs->cmd->args[1][1] == 'a')
		curs->cmd->args[2] ? history_a(me, curs->cmd->args[2], 0) :\
		history_a(me, find_hist_file(me), 1);
	else if (curs->cmd->args && curs->cmd->args[1] &&\
		curs->cmd->args[1][0] == '-' && \
		curs->cmd->args[1][1] == 'd')
		!curs->cmd->args[2] ? usage_history() :\
		rm_history(me, ft_atoi(curs->cmd->args[2]));
	else if (curs->cmd->args && curs->cmd->args[1] &&\
		curs->cmd->args[1][0] == '-' && \
		curs->cmd->args[1][1] == 'w')
		!curs->cmd->args[2] ? history_w(me, NULL, 0) :\
		history_w(me, curs->cmd->args[2], 0);
}
