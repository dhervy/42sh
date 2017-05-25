/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:41:16 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/06 12:02:31 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	tree_free(t_node *c)
{
	t_node	*p;

	while (c->left)
		c = c->left;
	while (c)
	{
		if (c->right)
			free(c->right);
		p = c->parent;
		free(c);
		c = p;
	}
}

void	trees_free(t_me *me)
{
	t_node	*t;

	t = me->trees;
	while (t)
	{
		tree_free(t);
		t = t->front;
	}
}

void	create_trees(t_me *me)
{
	t_cmd	*curs;

	curs = me->cmds;
	while (curs)
	{
		me->tcu = 0;
		while (curs && ft_strcmp(curs->name, ";") &&
		ft_strcmp(curs->name, "&&") &&
		ft_strcmp(curs->name, "||"))
		{
			node_push(me, curs);
			curs = curs->next;
		}
		push_tree(me, curs ?
		get_token(curs->name) : 0);
		curs ? curs = curs->next : 0;
	}
}
