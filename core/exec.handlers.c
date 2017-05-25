/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.hanlders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:33:11 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/05 13:35:02 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	set_handlers(t_node *curs)
{
	while (curs && curs->left)
		curs = curs->left;
	while (curs)
	{
		curs->handler = 0;
		if (curs->cmd->token == T_SLR && (!curs->parent ||
			curs->parent->cmd->token != T_PIPE) &&
			(curs->left && curs->left->cmd->token != T_SLR))
			curs->handler = &exec_sl_redir;
		else if (curs->cmd->token == T_PIPE)
			curs->handler = &exec_pipe;
		else if ((curs->cmd->token == T_DRR ||
			curs->cmd->token == T_SRR) && curs->left &&
			curs->left->cmd->token != T_PIPE)
			curs->handler = &exec_right_redir;
		else if (!curs->cmd->token)
			!curs->parent ? curs->handler = &exec_simple : 0;
		curs = curs->parent;
	}
}
