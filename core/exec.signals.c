/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:56:19 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/17 14:02:39 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	sig_hook_cz(int sig)
{
	(void)sig;
	psc("\n\n\t\t 42sh KILLED...\n", "38;5;128", 2);
	dup2(g_sigs.save_i, 1);
	close(g_sigs.save_i);
	dup2(g_sigs.save_o, 0);
	close(g_sigs.save_o);
	dup2(g_sigs.save_e, 0);
	close(g_sigs.save_e);
	exit(-1);
}

void	sig_int_quote(int sig)
{
	if (sig != SIGINT)
		return ;
	if (g_sigs.tmp)
	{
		ft_putchar('\n');
		mprompt(g_sigs.me, g_sigs.tmp->type, 0);
		g_sigs.tmp->line ? free(g_sigs.tmp->line) : 0;
		g_sigs.tmp->line = 0;
		g_sigs.tmp->t = 0;
		g_sigs.tmp->spos = 0;
		g_sigs.tmp->pos.x = 8;
		g_sigs.tmp->pos.y = 0;
	}
	else
		psc("\ndquote ", "38;5;201", 1);
}

void	sig_int(int sig)
{
	if (sig != SIGINT)
		return ;
	if (g_sigs.me)
	{
		ft_putchar('\n');
		mprompt(g_sigs.me, g_sigs.me->edl.type, 0);
		g_sigs.me->pprompt = 0;
		g_sigs.me->edl.line ? free(g_sigs.me->edl.line) : 0;
		g_sigs.me->edl.line = 0;
		g_sigs.me->edl.t = 0;
		g_sigs.me->edl.prompt_size = 8;
		g_sigs.me->edl.spos = 0;
		g_sigs.me->edl.pos.x = g_sigs.me->edl.prompt_size;
		g_sigs.me->edl.pos.y = 0;
	}
	else
		psc("\nsh -->  ", "38;5;201", 1);
	g_sigs.me->stop_edl = 1;
}

void	sig_exit_signal(t_me *me)
{
	(void)me;
	dup2(g_sigs.save_i, 1);
	close(g_sigs.save_i);
	dup2(g_sigs.save_o, 0);
	close(g_sigs.save_o);
	dup2(g_sigs.save_e, 0);
	close(g_sigs.save_e);
	exit(1);
}

int		han_pid(t_me *me, int r)
{
	me->go = me->go && r == EXIT_SUCCESS ? 1 : 0;
	if (r == SIGSEGV)
	{
		ft_putstr_fd("42sh: segmentation fault: ", 2);
		ft_putnbr(r);
		ft_putchar('\n');
		fexit(me);
	}
	else if (r == SIGABRT)
		ft_putendl_fd("42sh: abort ", 2);
	else if (r == SIGBUS)
		ft_putendl_fd("42sh: bus error ", 2);
	return (1);
}
