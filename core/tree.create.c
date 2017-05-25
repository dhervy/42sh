/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:38:04 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/06 11:29:08 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		modif_hdoc_tpipe(t_node *curs)
{
	t_node	*l;
	t_node	*r;

	l = curs->left;
	r = curs->right;
	curs->cmd->token == T_DLR ? curs->cmd->token = T_PIPE : 0;
	curs->cmd->name ? free(curs->cmd->name) : 0;
	curs->cmd->name = ft_strdup("|");
	curs->left = r;
	curs->right = l;
	curs->left->is_hdoc = 1;
	curs->left->cmd->token = T_HDOC;
}

void		node_push(t_me *me, t_cmd *cmd)
{
	t_node	*n;

	n = node_new(cmd);
	n->mode = NONE;
	if (!me->tcu)
		me->tcu = n;
	else if (cmd->token)
		push_parent(me, n);
	else if (!(cmd->token) && me->tcu->cmd->token)
		push_right(me, n);
}

void		push_tree(t_me *me, int intent)
{
	t_node *c;
	t_node *back;

	c = me->trees;
	back = 0;
	if (!me->tcu)
		return ;
	while (me->tcu->parent)
		me->tcu = me->tcu->parent;
	me->tcu->intent = intent;
	if (!c)
		me->trees = me->tcu;
	else
	{
		while (c->front)
		{
			back = c;
			c = c->front;
		}
		c->front = me->tcu;
		c->back = back;
	}
}

void		prepare_waitline(t_node *c)
{
	while (c && c->left)
		c = c->left;
	while (c)
	{
		if (c->cmd->token == T_PIPE)
		{
			while (c->parent && c->parent->cmd->token == T_PIPE)
				c = c->parent;
			c->mode = WAIT;
		}
		c = c->parent;
	}
}

int			prepare_tree(t_node *c)
{
	t_node *t;

	t = c;
	while (c)
	{
		if (c->cmd->token == T_DLR)
		{
			if (c->left && !c->left->cmd->token)
				modif_hdoc_tpipe(c);
			else
			{
				ft_putstr("Ambiguous input redirect.\n");
				return (0);
			}
		}
		c = c->left;
	}
	prepare_waitline(t);
	return (1);
}
