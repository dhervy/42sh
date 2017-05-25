/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 13:37:11 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 15:45:54 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**get_args(t_me *me, t_cmd *cmd, char **t, int i)
{
	char	**r;
	char	**afd;

	r = 0;
	cmd->args = 0;
	cmd->ac = 0;
	afd = 0;
	if (me && cmd && i >= 0)
	{
		--i;
		while (t && t[++i] &&
		!get_token(me->sh_c[i]))
		{
			if (!is_afd(me->sh_c[i]))
				r = tab_add(r, t[i]);
			else
				afd = tab_add(afd, t[i]);
		}
		cmd->args = cmd->name && t ? r : NULL;
		cmd->ac = tab_size(cmd->args);
	}
	return (afd);
}

void	cmd_create(t_me *me)
{
	int i;

	i = -1;
	if (!me->sh_c)
		return ;
	while (me->sh_c[++i] &&
		!ft_strcmp(me->sh_c[i], ";"))
		;
	me->sh_c = &(me->sh_c[i]);
	if (!me->sh_c)
		return ;
	i = -1;
	while (me->sh_c[++i])
	{
		if (!get_token(me->sh_c[i]))
			push_cmd(me, i);
		else if (get_token(me->sh_c[i]))
			push_deli(me, me->sh_c[i], i);
		while (me->sh_c[i + 1] && !get_token(me->sh_c[i + 1]))
			i++;
		if (me->sh_c[++i] && get_token(me->sh_c[i]))
			push_deli(me, me->sh_c[i], i);
		if (!(me->sh_c[i]))
			return ;
	}
}

char	*replace_tilde(t_me *me, char *s)
{
	int		i;
	char	*tmp;
	char	*home;

	i = -1;
	tmp = NULL;
	if (!s)
		return (NULL);
	if ((home = get_edt(me->e, "HOME")) == NULL)
		return (s);
	while (s[++i])
	{
		if (s[i] == '~' && s[i + 1] && s[i + 1] == '/')
		{
			tmp = ft_strndup(s, i);
			tmp = ft_strjoinfree(tmp, home, 1);
			tmp = ft_strjoinfree(tmp, &s[i + 1], 1);
			free(s);
			s = ft_strdup(tmp);
			free(tmp);
			tmp = NULL;
		}
	}
	home ? free(home) : 0;
	return (s);
}

char	*find_read_var(t_me *me, char *s)
{
	int		i;
	char	*name;
	t_read	*tmp;

	i = -1;
	tmp = me->var_read;
	name = NULL;
	while (s[++i] && s[i] != ' ')
	{
		if (!name)
			name = ft_strndup(&s[i], 1);
		else
			name = ft_strjoinfree(name, ft_strndup(&s[i], 1), 3);
	}
	while (tmp && ft_strcmp(tmp->name, name))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(tmp->name, name))
	{
		name ? free(name) : 0;
		return (tmp->value);
	}
	name ? free(name) : 0;
	return (NULL);
}

int		read_kwo(t_me *me)
{
	int		i;
	char	*tmp;
	char	**tmp2;

	i = -1;
	me->sh_c = 0;
	while ((me->edl.line)[++i])
		ft_strchr("\t", (me->edl.line)[i]) ? me->edl.line[i] = ' ' : 0;
	tmp = clean_line(me->edl.line);
	tmp ? me->edl.line = tmp : 0;
	tmp = check_dquotes(me, me->edl.line);
	tmp ? me->edl.line = tmp : 0;
	tmp = replace_tilde(me, me->edl.line);
	tmp ? me->edl.line = tmp : 0;
	tmp = replace_variables(me, me->edl.line);
	tmp ? me->edl.line = tmp : 0;
	tmp = replace_read_variables(me, me->edl.line);
	tmp ? me->edl.line = tmp : 0;
	if (me->edl.line)
	{
		tmp2 = msplit(me->edl.line, ' ');
		me->sh_c = tmp2 ? tmp2 : ft_strsplit(me->edl.line, ' ');
	}
	return (me->sh_c ? 1 : 0);
}
