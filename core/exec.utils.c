/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:29:44 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 02:54:47 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_node	*prepare_exec(t_me *me, t_node *curs)
{
	(void)me;
	while (curs->left)
		curs = curs->left;
	return (curs);
}

char	*remplace_p_ex_line2(char *str, char *tmp, int i)
{
	char	*debut;

	debut = NULL;
	debut = ft_strndup(str, i - 1);
	debut = ft_strjoinfree(debut, tmp, 3);
	free(str);
	return (debut);
}
