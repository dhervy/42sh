/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:46:05 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/17 14:03:19 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	close_fds(t_node *curs)
{
	while (curs)
	{
		if (curs->right)
			close(curs->right->fd_out);
		if (curs->left)
			close(curs->left->fd_out);
		curs = curs->left;
	}
}

void	wait_pipelines(t_me *me, t_node *curs)
{
	if (curs && curs->cmd->token == T_PIPE
		&& curs->mode == WAIT)
		while (curs && curs->cmd->token == T_PIPE)
		{
			if (curs->left && !curs->left->cmd->token)
			{
				close(curs->left->pfd[0]);
				close(curs->left->pfd[1]);
				waitpid(curs->left->pid, &(curs->left->ret), 0);
				if (!is_builtin(curs->left->cmd->name))
					han_pid(me, curs->left->ret);
				else
					me->go = 1;
			}
			close(curs->right->pfd[0]);
			close(curs->right->pfd[1]);
			waitpid(curs->right->pid, &(curs->right->ret), 0);
			if (!is_builtin(curs->right->cmd->name))
				han_pid(me, curs->right->ret);
			else
				me->go = 1;
			curs = curs->left;
		}
}

void	exec_mpipe(t_me *me, t_node *curs)
{
	char	*p;

	p = 0;
	if (curs->is_hdoc && curs->thdoc)
		ft_putstr(curs->thdoc);
	else if (!curs->cmd->token)
	{
		if (is_builtin(curs->cmd->name))
			execute_builtin(me, curs);
		else if ((p = get_path(me, curs->cmd->name)))
			execve(p, curs->cmd->args, me->e);
		else
			merror(me, curs->cmd->name, 1);
	}
	else if (curs->cmd->token == T_SLR)
		exec_aleft_redir(me, curs);
}

int		exec_apipe(t_me *me, t_node *curs, int is_last)
{
	if (pipe(curs->pfd) == -1 || !curs)
		return (0);
	if (!(curs->pid = fork()))
	{
		sig_catch_child(me);
		if (curs->is_hdoc)
			heredoc_loop(me, curs);
		me->fd_in > -1 ? dup2(me->fd_in, 0) : 0;
		if (!is_last)
			dup2(curs->pfd[1], 1);
		else if (curs->parent->parent && curs->parent->parent->fd_out >= 0)
			dup2(curs->parent->parent->fd_out, 1);
		close(curs->pfd[0]);
		process_afds(curs->cmd->afd);
		exec_mpipe(me, curs);
		if (!curs->is_hdoc && !is_builtin(curs->cmd->name))
			ft_putendl_fd("42sh: Not an executable", 2);
		exit(-1);
	}
	else
	{
		close(curs->pfd[1]);
		me->fd_in = add_iufd(curs->pfd[0]);
	}
	return (curs->pid >= 0 ? 1 : -1);
}

int		exec_pipe(t_me *me, t_node *curs)
{
	int			is_last;

	if (!curs || !curs->left)
		return (-1);
	is_last = !curs->parent || curs->parent->cmd->token != T_PIPE ? 1 : 0;
	if (!curs->left->cmd->token || curs->left->cmd->token == T_HDOC ||
	curs->left->cmd->token == T_SLR)
		exec_apipe(me, curs->left, 0);
	else if (curs->left->cmd->token == T_DRR || curs->left->cmd->token == T_SRR)
	{
		me->fd_in = add_iufd(open(curs->left->right->cmd->name,
		O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO));
	}
	curs->parent ? mredir(me, curs->parent) : 0;
	exec_apipe(me, curs->right, is_last);
	wait_pipelines(me, curs);
	return (1);
}
