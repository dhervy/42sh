/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:36:55 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/05 16:37:30 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_node		*node_new(t_cmd *cmd)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	n->handler = 0;
	n->is_hdoc = 0;
	n->back = 0;
	n->front = 0;
	n->left = 0;
	n->parent = 0;
	n->right = 0;
	n->intent = 0;
	n->thdoc = 0;
	n->cmd = cmd;
	n->fd_out = -1;
	return (n);
}

void		push_parent(t_me *me, t_node *n)
{
	me->tcu->parent = n;
	n->left = me->tcu;
	me->tcu = n;
}

void		push_right(t_me *me, t_node *n)
{
	me->tcu->right = n;
	n->parent = me->tcu;
}
