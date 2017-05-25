/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 13:44:43 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 02:13:35 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	init_mcmd(t_cmd *new, char *name)
{
	new->name = ft_strdup(name);
	new->args = 0;
	new->next = 0;
	new->afd = 0;
}

int		var_name_size(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i] && s[i] != ' ' && s[i] != '\"')
		;
	return (i >= 0 ? i : 0);
}

char	**tab_dup(char **t)
{
	char	**r;
	int		i;

	i = 0;
	if (tab_size(t) < 1)
		return (0);
	r = malloc(sizeof(char*) * tab_size(t) + 1);
	while (t[i])
	{
		r[i] = ft_strdup(t[i]);
		++i;
	}
	r[i] = 0;
	return (r);
}

void	restor_select(t_me *me)
{
	t_hist	*tmp;

	if (me->hi)
	{
		tmp = me->hi;
		while (tmp && tmp->next && tmp->select == 0)
			tmp = tmp->next;
		tmp->select = 0;
	}
}

void	down_hist2(t_me *me, t_edl *edl, t_hist *t, int c)
{
	restore_pos(me, (t_vec){edl->pos.x - edl->prompt_size, edl->pos.y});
	edl->pos.x = edl->prompt_size;
	edl->pos.y = 0;
	edl->spos = 0;
	exec_mode(me, "cd");
	edl->line ? free(edl->line) : 0;
	edl->line = NULL;
	while (t && t->name && t->name[++c])
		insert_key(me, edl, t->name[c]);
	t->select = 1;
}
