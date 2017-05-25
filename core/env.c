/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 11:30:43 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/06 10:34:14 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	do_set(t_me *me, t_cmd *a, int *i)
{
	me->e = assign_env(me->e, a->args[*i],
	a->args[*i + 1] && !ft_strcmp(a->args[*i + 1], "1") ? 1 : 0);
}

int		mset_error(t_me *me, t_cmd *a)
{
	(void)me;
	if (a && a->args && !a->args[1])
	{
		psc("\e[0m⦿  setenv  \e[38;5;196m\t\t\t➣ \e[38;5;154m \
		not enough arguments\n\e[0m", "38;5;154", 2);
		return (0);
	}
	if (tab_size(&(a->args[1])) % 2)
	{
		psc("\e[0m⦿  setenv  \e[38;5;196m\t\t\t➣ \e[38;5;154m \
		wrong number of arguments\n\e[0m", "38;5;154", 2);
		return (0);
	}
	return (1);
}

void	msetenv(t_me *me, t_cmd *a)
{
	char	*t;
	int		i;

	i = 1;
	if (!me || !a || !mset_error(me, a))
		return ;
	while (a && a->args && a->args[i] && a->args[i + 1])
	{
		t = ft_strjoin(a->args[i], "=");
		if (env_isin(me->e, t))
			env_modif(me->e, a->args[i],
			a->args[i + 1]);
		if (!env_isin(me->e, t) && a->args[i])
			me->e = env_add(me->e, a->args[i],
			a->args[i + 1]);
		free(t);
		i += 2;
	}
}

void	munset_env(t_me *me, t_cmd *a)
{
	int		i;

	i = 0;
	if (!a || !me)
		return ;
	if (!a->args || !a->args[1])
		psc("\e[0m⦿  unsetenv\e[38;5;196m\t\t\t➣ \e[38;5;154m \
		not enough arguments\n\e[0m", "38;5;154", 2);
	else
		while (a->args[++i])
		{
			if (me->e)
				me->e = env_sub(me->e, a->args[i]);
		}
}
