/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:29:45 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/13 14:51:17 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*clean_cd_path(t_me *me, char *s)
{
	char	*tmp[2];

	if (!s || !me)
		return (0);
	if (start_by(s, "~") && me->e)
	{
		tmp[1] = s;
		tmp[0] = get_edt(me->e, "HOME");
		s = ft_strjoin(tmp[0], s + 1);
		free(tmp[0]);
		free(tmp[1]);
	}
	return (s);
}

char	*cd_path(t_me *me, t_cmd *cmd)
{
	char *s[2];

	if (!cmd || !cmd->args)
		return (0);
	if (cmd->args[1] && cmd->args[1][0] == '-')
	{
		s[0] = get_edt(me->e, "OLDPWD");
		s[1] = ft_strjoin(s[0], cmd->args[1] + 1);
		free(s[0]);
		return (s[1]);
	}
	if (!cmd->args[1])
		return (get_edt(me->e, "HOME"));
	return (clean_cd_path(me, ft_strdup(cmd->args[1])));
}

int		mcd_errors(char c, char *s)
{
	if (!s)
		return (0);
	if (c == 'A' && access(s, F_OK))
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(s);
		ft_putchar('\n');
		return (0);
	}
	if (c == 'B' && chdir(s) < 0)
	{
		if (!access(s, R_OK))
			ft_putstr("cd: not a directory: ");
		else
			ft_putstr("cd: Permission denied: ");
		ft_putstr(s);
		ft_putchar('\n');
		return (0);
	}
	return (1);
}

void	end_cd(t_me *me)
{
	char *s;

	s = getcwd(ft_strnew(1024), 1024);
	if (env_isin(me->e, "PWD="))
		env_modif(me->e, "PWD", s);
	else
		me->e = env_add(me->e, "PWD", s);
	free(s);
}

void	mcd(t_me *me, t_cmd *a)
{
	char	*s;
	char	*t;

	t = cd_path(me, a);
	if (!mcd_errors('A', t))
	{
		t ? free(t) : 0;
		return ;
	}
	s = getcwd(ft_strnew(1024), 1024);
	if (env_isin(me->e, "OLDPWD="))
		env_modif(me->e, "OLDPWD", s);
	else
		me->e = env_add(me->e, "OLDPWD", s);
	free(s);
	if (!mcd_errors('B', t))
	{
		t ? free(t) : 0;
		return ;
	}
	end_cd(me);
	t ? free(t) : 0;
}
