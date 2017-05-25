/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.p_ex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertojo <tbertojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 23:14:25 by tbertojo          #+#    #+#             */
/*   Updated: 2017/05/03 15:26:30 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*remplace_p_ex_line(char *str, char *tmp, int i, int t)
{
	char	*debut;
	char	*fin;

	debut = NULL;
	fin = NULL;
	debut = ft_strndup(str, i - 1);
	t ? fin = ft_strdup(&str[i + t]) : 0;
	debut = ft_strlen(debut) ? ft_strjoinfree(debut, " ", 1) : debut;
	debut = ft_strjoinfree(debut, tmp, 3);
	t ? debut = ft_strjoinfree(debut, fin, 3) : 0;
	free(str);
	return (debut);
}

void	p_ex_if(t_me *me, char **str, int i)
{
	char	*tmp;

	tmp = NULL;
	if ((*str)[i + 1] && (*str)[i + 1] != ' ' && (ft_isdigit((*str)[i + 1]) ||\
	(((*str)[i + 1] == '-') && (*str)[i + 2] && ft_isdigit((*str)[i + 2]))) \
	&& ((tmp = remplace_line(me, ft_atoi(&(*str)[i + 1]))) != NULL))
		(*str) = remplace_p_ex_line2((*str), tmp, i);
	else if ((*str)[i + 1] && (*str)[i + 1] == '!' && (!(*str)[i + 2] ||\
	((*str)[i + 2] && (*str)[i + 2] == ' ')) &&\
	((tmp = last_elem_hist(me)) != NULL))
		(*str) = remplace_p_ex_line((*str), tmp, i, 2);
	else if ((*str)[i + 1] && (*str)[i + 1] == '!' && (*str)[i + 2]\
	&& (*str)[i + 2] == ':' && (*str)[i + 3] && (*str)[i + 3] != ' ' &&\
	((tmp = n_elem_hist(me, ft_atoi(&(*str)[i + 3]), NULL)) != NULL))
		(*str) = remplace_p_ex_line((*str), tmp, i, 4);
	else if ((*str)[i + 1] && (*str)[i + 1] == '$' &&\
	(!(*str)[i + 2] || ((*str)[i + 2] &&\
	(*str)[i + 2] == ' ')) && ((tmp = find_last_param(me, NULL)) != NULL))
		(*str) = remplace_p_ex_line((*str), tmp, i, 2);
	else if ((*str)[i + 1] && (*str)[i + 1] == '*' && (!(*str)[i + 2] || \
	((*str)[i + 2] && (*str)[i + 2] == ' ')) && ((tmp = find_param(me, NULL))))
		(*str) = remplace_p_ex_line((*str), tmp, i, 2);
	else if ((*str)[i + 1] && (*str)[i + 1] != ' ' &&\
	((tmp = find_same_hist(&(*str)[i + 1], me, 0, 0)) != NULL))
		(*str) = remplace_p_ex_line((*str), tmp, i, 0);
}

void	p_ex_error(t_node *curs, char *str)
{
	if (str && p_ex(curs->cmd->args))
	{
		ft_putstr("42sh: ");
		ft_putstr(str);
		ft_putendl(": event not found");
	}
	else
		str ? ft_putendl(str) : 0;
}

void	remplace_p_ex(t_me *me, t_node *curs)
{
	int		i;
	char	*str;

	str = NULL;
	i = -1;
	str = tab_to_str(curs->cmd->args);
	while (str[++i])
	{
		if (str[i] == '\"')
			while (str[++i] != '\"')
				;
		if (str[i] == '\'')
			while (str[++i] != '\'')
				;
		if (str[i] == '!')
			p_ex_if(me, &str, i);
	}
	tab_free(curs->cmd->args);
	free(curs->cmd->name);
	curs->cmd->args = ft_strsplit(str, ' ');
	curs->cmd->name = ft_strdup(curs->cmd->args[0]);
	p_ex_error(curs, str);
	remplace_last_hist(me, str);
	free(str);
}

int		p_ex(char **args)
{
	int		i;
	char	*str;

	i = -1;
	str = NULL;
	str = tab_to_str(args);
	while (str && str[++i])
	{
		if (str[i] == '\"')
			while (str[i + 1] && str[++i] != '\"')
				;
		if (str[i] == '\'')
			while (str[i + 1] && str[++i] != '\'')
				;
		if (str[i] == '!')
		{
			free(str);
			return (1);
		}
	}
	str ? free(str) : 0;
	return (0);
}
