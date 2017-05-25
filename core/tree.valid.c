/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:42:11 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/17 14:02:04 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		verif_node(t_node *c)
{
	char	token;

	if (!c || !c->cmd)
		return (0);
	token = c->cmd->token;
	if (token == T_PIPE ||
		token == T_SRR ||
		token == T_DRR ||
		token == T_SLR ||
		token == T_DLR)
		if (!c->left || !c->right)
			return (0);
	return (1);
}

int		valid_tree(t_node *curs)
{
	while (curs->left)
		curs = curs->left;
	while (curs)
	{
		if (!verif_node(curs))
		{
			ft_putstr_fd("42sh: Wrong format for node \"", 2);
			ft_putstr_fd(curs->cmd ?
			curs->cmd->name : "null", 2);
			ft_putendl_fd("\"", 2);
			return (0);
		}
		curs = curs->parent;
	}
	return (1);
}
