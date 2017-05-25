/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:58:44 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/17 14:02:18 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*get_abr(char *s)
{
	if (*s == '.' &&
	(*s + 1) &&
	*s + 1 == '/')
		return (s + 2);
	return (s);
}

int		exec_simple2(t_me *me, t_node *curs)
{
	if (is_builtin(curs->cmd->name))
	{
		execute_builtin(me, curs);
		return (1);
	}
	return (0);
}

void	exec_simple3(t_me *me, t_node *curs, char *p)
{
	if (!(curs->pid = fork()))
	{
		sig_catch_child(me);
		process_afds(curs->cmd->afd);
		execve(p, curs->cmd->args, me->e);
		ft_putendl_fd("42sh: Not an executable", 2);
		exit(-1);
	}
	else
	{
		waitpid(curs->pid, &(curs->ret), WUNTRACED);
		free(p);
		!is_builtin(curs->cmd->name) ? han_pid(me, curs->ret) : (me->go = 1);
	}
}

int		exec_simple(t_me *me, t_node *curs)
{
	char	*p;
	char	*a;

	p = 0;
	if (exec_simple2(me, curs))
		return (1);
	if (!curs || !curs->cmd)
		return (-1);
	a = curs->cmd->name;
	if ((p = get_path(me, curs->cmd->name)))
		exec_simple3(me, curs, p);
	else if (!(me->go = 0))
		merror(me, curs->cmd->name, 1);
	return (1);
}
