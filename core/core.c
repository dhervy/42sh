/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:01:29 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 03:26:59 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	process_cmds(t_me *me)
{
	t_node	*c;

	c = me->trees;
	while (c)
	{
		tree_exec(me, c);
		if ((c->intent == T_AND && !me->go) ||
		(c->intent == T_OR && me->go))
			c = c->front;
		c ? c = c->front : 0;
	}
}

void	execute_line(t_me *me)
{
	if (read_kwo(me))
	{
		me->go = 1;
		me->o_shc = me->sh_c;
		cmd_create(me);
		create_trees(me);
		process_cmds(me);
		cmds_free(me);
		if (me->o_shc)
			tab_free(me->o_shc);
		trees_free(me);
		me->tcu = 0;
		me->tc = 0;
		me->trees = 0;
	}
}

void	edl_loop(t_me *me)
{
	long int k;

	me->edl.spos = 0;
	me->edl.line = 0;
	me->edl.prompt_size = 8;
	me->edl.pos.x = me->edl.prompt_size;
	me->edl.pos.y = 0;
	me->edl.ccmode = 0;
	me->edl.select[0] = -1;
	me->edl.select[1] = -1;
	me->edl.clipboard = 0;
	while (42)
	{
		k = 0;
		read(0, (char*)(&k), 6);
		get_wterm(me);
		execute_key(me, &(me->edl), k);
	}
}

void	init_core(t_me *me, char **env)
{
	char *shlvl[2];

	me->oe = env;
	me->e = env_cpy(me->oe);
	if (me->e)
	{
		me->name_term = get_edt(me->e, "TERM");
		if (*shlvl && env_isin(me->e, "SHLVL="))
		{
			shlvl[0] = get_edt(me->e, "SHLVL");
			shlvl[1] = ft_itoa(1 + ft_atoi(shlvl[0]));
			shlvl[0] ? free(shlvl[0]) : 0;
			env_modif(me->e, "SHLVL", shlvl[1]);
			shlvl[1] ? free(shlvl[1]) : 0;
		}
		else
			me->e = env_add(me->e, "SHLVL", "0");
	}
	init_core_end(me);
}

int		main(int ac, char **av, char **env)
{
	t_me me;

	(void)ac;
	(void)av;
	if (tcgetattr(0, &me.save) == -1)
		return (-1);
	me.var_read = NULL;
	init_core(&me, env);
	import_config(&me);
	sig_catch(&me);
	if (!init_term(&me))
	{
		ft_putendl("Unable to start 42 shell corectly");
		return (0);
	}
	history_r(&me, find_hist_file(&me), 3);
	mprompt(&me, me.edl.type, 1);
	edl_loop(&me);
	if (me.e)
		tab_free(me.e);
}
