/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 11:24:24 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 18:00:04 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		**env_cpy(char **e)
{
	int		i;
	char	*t;
	char	**n;

	i = -1;
	if (e && *e)
	{
		n = malloc(sizeof(char*) * (tab_size(e) + 1));
		while (e[++i])
			n[i] = ft_strdup(e[i]);
		n[i] = NULL;
	}
	else
	{
		n = malloc(sizeof(char*) * 5);
		n[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:\
		/sbin:/usr/local/bin:/opt/X11/bin:/usr/local/munki");
		n[1] = ft_strdup("SHLVL=1");
		n[2] = ft_strdup("USER=Correction_Boss");
		t = getcwd(ft_strnew(1024), 1024);
		n[3] = ft_strjoin("PWD=", t);
		free(t);
		n[4] = NULL;
	}
	return (n);
}

char		**assign_env(char **e, char *a, int ov)
{
	char		*value;
	char		*name;
	char		*t;
	char		**r;

	r = NULL;
	if (ssn(a, "="))
	{
		name = ft_strndup(a, mlen(a, '='));
		value = ft_strdup(a + mlen(a, '=') + 1);
		t = ft_strjoin(name, "=");
		if (e && env_isin(e, t))
			r = ov ? env_modif(e, name, value) : e;
		else
			r = env_add(e, name, value);
		free(t);
		free(name);
		free(value);
	}
	return (r);
}

void		exec_menv_cmd(t_me *me, char **args, char **env)
{
	char	*p;
	int		v[2];

	if (!args)
		return ;
	if ((p = get_path(me, args[0])))
	{
		if (!(v[0] = fork()))
		{
			sig_catch_child(me);
			execve(p, args, env);
			p ? free(p) : 0;
			ft_putendl("42sh: Not an executable");
			exit(-1);
		}
		else
		{
			waitpid(v[0], &v[1], WUNTRACED);
			han_pid(me, v[1]);
			p ? free(p) : 0;
		}
	}
	else
		merror(me, args[0], 1);
}

void		menv_suite(t_me *me, t_cmd *a, int *i)
{
	if (ssn(a->args[*i], "="))
	{
		while (a->args[*i] && ssn(a->args[*i], "="))
		{
			me->pe = assign_env(me->pe, a->args[*i], 1);
			++(*i);
		}
	}
	if (a->args[*i])
		exec_menv_cmd(me, &(a->args[*i]), me->pe);
	else if (me->pe)
		print_env(me->pe);
	me->pe ? tab_free(me->pe) : 0;
	me->pe = 0;
}

void		menv(t_me *me, t_cmd *a)
{
	int		i;
	int		op;

	if (!a || !a->args || !me)
		return ;
	op = a->args[1] &&
	ssn(a->args[1], "-") && ssn(a->args[1], "i") ? 1 : 0;
	i = op ? 2 : 1;
	me->pe ? tab_free(me->pe) : 0;
	me->pe = op ? 0 : env_cpy(me->e);
	if ((a->args[i]))
		menv_suite(me, a, &i);
	else if (!op)
		print_env(me->e);
}
