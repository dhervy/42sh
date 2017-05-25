/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:20:22 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 15:45:48 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_key(long int k)
{
	if (k == UP ||
	k == DOWN ||
	k == LEFT ||
	k == RIGHT ||
	k == CUP ||
	k == CDOWN ||
	k == CLEFT ||
	k == CRIGHT ||
	k == OUP ||
	k == ODOWN ||
	k == OLEFT ||
	k == ORIGHT ||
	k == HOME ||
	k == END ||
	k == DEL ||
	k == ENTER ||
	k == TAB ||
	k == ESC ||
	k == SPC ||
	k == OX ||
	k == OC ||
	k == CL ||
	k == OV)
		return (1);
	return (0);
}

char	*replace_read_variables(t_me *me, char *s)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!me->var_read)
		return (s);
	while (s[++i])
	{
		if (s[i] == '$' && (i == 0 || (s[i - 1] == ' ')) &&\
		s[i + 1] && s[i + 1] != ' ')
		{
			tmp = ft_strndup(s, i);
			tmp = ft_strjoinfree(tmp, find_read_var(me, &s[i + 1]), 1);
			while (s[i] && s[i] != ' ')
				i++;
			tmp = ft_strjoinfree(tmp, &s[i], 1);
			free(s);
			s = ft_strdup(tmp);
			free(tmp);
			tmp = NULL;
			i = -1;
		}
	}
	return (s);
}

int		ft_tablen(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
