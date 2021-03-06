/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mexit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:45:59 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/03 14:46:34 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		mexit(int e)
{
	exit(e);
	return (1);
}

int		fexit(t_me *me)
{
	me->cmds ? cmds_free(me) : 0;
	exit(-1);
	return (1);
}
