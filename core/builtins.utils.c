/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:29:13 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 17:59:47 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	mecho(t_me *me, char **keys)
{
	int i;

	i = -1;
	(void)me;
	while (keys[++i])
	{
		ft_putstr(keys[i]);
		keys[i + 1] ? ft_putstr(" ") : 0;
	}
	ft_putstr("\n");
}

void	execute_builtin2(t_me *me, t_node *curs)
{
	if (!ft_strcmp(curs->cmd->name, "printenv"))
		print_env(me->e);
	else if (!ft_strcmp(curs->cmd->name, "echo") &&
	curs->cmd->args && curs->cmd->args[1])
		mecho(me, &(curs->cmd->args[1]));
	else if (!ft_strcmp(curs->cmd->name, "read"))
		ft_read(me, curs->cmd);
}

int		execute_builtin(t_me *me, t_node *curs)
{
	if (!me || !curs || !curs->cmd)
		return (0);
	if (curs && !ft_strcmp(curs->cmd->name, "exit"))
	{
		history_a(me, find_hist_file(me), 1);
		exit(curs->cmd->args && curs->cmd->args[1]
		? ft_atoi(curs->cmd->args[1]) : 0);
	}
	else if (!ft_strcmp(curs->cmd->name, "cd"))
		mcd(me, curs->cmd);
	else if (!ft_strcmp(curs->cmd->name, "history"))
		history(me, curs);
	else if (!ft_strcmp(curs->cmd->name, "setenv"))
		msetenv(me, curs->cmd);
	else if (!ft_strcmp(curs->cmd->name, "unsetenv"))
		munset_env(me, curs->cmd);
	else if (!ft_strcmp(curs->cmd->name, "env"))
		menv(me, curs->cmd);
	else
		execute_builtin2(me, curs);
	return (1);
}

int		is_builtin(char *s)
{
	return ((!ft_strcmp(s, "exit") ||
	!ft_strcmp(s, "env") ||
	!ft_strcmp(s, "setenv") ||
	!ft_strcmp(s, "unsetenv") ||
	!ft_strcmp(s, "printenv") ||
	!ft_strcmp(s, "read") ||
	!ft_strcmp(s, "history") ||
	!ft_strcmp(s, "echo") ||
	!ft_strcmp(s, "cd")) ? 1 : 0);
}
