/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 12:07:35 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/31 14:18:15 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	end_execute_enter(t_me *me, t_edl *edl)
{
	me->pprompt = 1;
	edl->line ? free(edl->line) : 0;
	edl->line = 0;
	me->trees = 0;
	me->l = me->hi ? hi_end(me->hi) : 0;
	edl_default(edl);
	me->edl.ccmode = 0;
}
