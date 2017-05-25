/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.left.redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:41:06 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/17 14:03:14 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_node		*get_last_left(t_node *c)
{
	if (!c)
		return (0);
	while (c->parent && c->parent->cmd->token == T_SLR)
		c = c->parent;
	return (c);
}

void		exec_aleft_redir(t_me *me, t_node *curs)
{
	int		fd;
	char	*p;
	t_node	*lcmd;

	p = 0;
	if ((fd = open(get_last_left(curs)->right->cmd->name, O_RDWR)) != -1)
	{
		dup2(fd, 0);
		lcmd = !(curs->left->cmd->token) ? curs->left : 0;
		lcmd = curs->left->cmd->token == T_PIPE ? curs->left->right : lcmd;
		lcmd ? p = get_path(me, lcmd->cmd->name) : 0;
		if (curs->parent && (curs->parent->cmd->token == T_SRR ||
			curs->parent->cmd->token == T_DRR))
			dup2(curs->parent->fd_out, 1);
		process_afds(curs->cmd->afd);
		p ? execve(p, lcmd->cmd->args, me->e) : merror(me, lcmd->cmd->name, 1);
		close(fd);
	}
}

int			exec_sl_redir(t_me *me, t_node *curs)
{
	if (curs->parent && (curs->parent->cmd->token == T_SRR ||
		curs->parent->cmd->token == T_DRR))
	{
		curs->parent->handler = 0;
		mredir(me, curs->parent);
	}
	if (!(curs->left->pid = fork()))
	{
		sig_catch_child(me);
		exec_aleft_redir(me, curs);
		ft_putendl("42sh: Not an executable");
		exit(-1);
		return (-1);
	}
	else
	{
		waitpid(curs->left->pid, &curs->ret, WUNTRACED);
		han_pid(me, curs->ret);
	}
	curs->parent ? close(curs->parent->fd_out) : 0;
	return (1);
}
