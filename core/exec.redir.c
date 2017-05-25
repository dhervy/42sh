/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:49:58 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/17 14:02:46 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		mcp(t_me *me, t_node *curs)
{
	char	*file;
	char	*l;
	int		fd[2];

	(void)me;
	file = 0;
	l = 0;
	if ((fd[0] = open(curs->left->right->cmd->name, O_RDONLY)) == -1)
		exit(-1);
	if ((fd[1] = open(curs->right->cmd->name,
		O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
		exit(-1);
	while (get_next_line(fd[0], &l))
	{
		ft_putendl_fd(l, fd[1]);
		l ? free(l) : 0;
	}
	l ? free(l) : 0;
	close(fd[0]);
	close(fd[1]);
	return (1);
}

void	handle_wait(t_me *me, t_node *curs)
{
	if (!curs)
		return ;
	wait(&(curs->ret));
	han_pid(me, curs->ret);
}

int		exec_right_redir(t_me *me, t_node *curs)
{
	char	*p;

	if (!curs->left || !mredir(me, curs))
		return (-1);
	if (!curs->left->cmd->token)
	{
		if ((curs->pid = !fork()))
		{
			sig_catch_child(me);
			dup2(curs->fd_out, STDOUT_FILENO);
			process_afds(curs->cmd->afd);
			p = get_path(me, curs->left->cmd->name);
			p ? execve(p, curs->left->cmd->args, me->e) : 0;
			ft_putendl_fd("42sh: Not an executable", 2);
			exit(-1);
			return (-1);
		}
		else
			handle_wait(me, curs);
	}
	else if (curs->left->cmd->token == T_SRR || curs->left->cmd->token == T_DRR)
		mcp(me, curs);
	close(curs->fd_out);
	return (1);
}

int		mredir(t_me *me, t_node *curs)
{
	int		fd;

	(void)me;
	fd = -1;
	if (curs->cmd->token == T_SRR &&
		(fd = open(curs->right->cmd->name, O_RDWR | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		ft_putstr_fd("zsh: no such file or directory:", 2);
		ft_putendl_fd(curs->right->cmd->name, 2);
		return (-1);
	}
	if (curs->cmd->token == T_DRR &&
		(fd = open(curs->right->cmd->name, O_RDWR | O_APPEND | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		ft_putstr_fd("zsh: no such file or directory:", 2);
		ft_putendl_fd(curs->right->cmd->name, 2);
		return (-1);
	}
	curs->fd_out = fd;
	add_iufd(fd);
	return (fd == -1 ? 0 : 1);
}
