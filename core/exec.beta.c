/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.beta.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:29:06 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/26 18:32:42 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		exit_exec_tree(t_node *curs, t_me *me)
{
	(void)me;
	dup2(g_sigs.save_i, 0);
	close(g_sigs.save_i);
	dup2(g_sigs.save_o, 1);
	close(g_sigs.save_o);
	dup2(g_sigs.save_e, 2);
	close(g_sigs.save_e);
	close_fds(curs);
	return (1);
}

int		add_iufd(int fd)
{
	g_sigs.fds_iu = join_free(g_sigs.fds_iu,
	join_free(ft_itoa(fd), ft_strdup(" ")));
	return (fd);
}

void	process_iufds(void)
{
	char	**t;
	int		i;

	if (!g_sigs.fds_iu)
		return ;
	t = ft_strsplit(g_sigs.fds_iu, ' ');
	i = -1;
	while (t[++i])
		close(ft_atoi(t[i]));
	tab_free(t);
	free(g_sigs.fds_iu);
	g_sigs.fds_iu = 0;
}

int		tree_exec(t_me *me, t_node *curs)
{
	if (!valid_tree(curs))
		return (-1);
	g_sigs.save_i = dup(0);
	g_sigs.save_o = dup(1);
	g_sigs.save_e = dup(2);
	me->fd_in = -1;
	if (!prepare_tree(curs) && exit_exec_tree(curs, me))
		return (-1);
	set_handlers(curs);
	curs = prepare_exec(me, curs);
	g_sigs.fds_iu = 0;
	while (curs)
	{
		if (me->hi && me->hi->next && p_ex(curs->cmd->args))
			remplace_p_ex(me, curs);
		curs->handler ? curs->handler(me, curs) : 0;
		curs = curs->parent;
	}
	process_iufds();
	exit_exec_tree(curs, me);
	close(me->fd_in);
	return (1);
}
