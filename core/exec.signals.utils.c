/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.signals.utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:58:34 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/06 11:25:29 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	sig_catch(t_me *me)
{
	(void)me;
	signal(SIGINT, (void(*)())sig_int);
	signal(SIGTSTP, (void(*)())sig_int);
	signal(SIGQUIT, (void(*)())sig_hook_cz);
}

void	sig_catch_child(t_me *me)
{
	(void)me;
	signal(SIGINT, (void(*)())sig_exit_signal);
	signal(SIGTSTP, (void(*)())sig_exit_signal);
	signal(SIGQUIT, (void(*)())sig_exit_signal);
}
