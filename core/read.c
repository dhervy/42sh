/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <dhervy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 00:06:55 by dhervy            #+#    #+#             */
/*   Updated: 2017/05/03 15:45:08 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_read	*ft_creat_read(t_read *new, char *name, char *value)
{
	new = (t_read*)malloc(sizeof(t_read));
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

int		ft_check_read(t_me *me, char *name, char *value)
{
	t_read	*tmp;

	tmp = me->var_read;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_push_read(t_me *me, char *name, char *value)
{
	t_read	*tmp;
	t_read	*new;

	new = NULL;
	if (ft_check_read(me, name, value))
		return ;
	tmp = me->var_read;
	new = ft_creat_read(new, name, value);
	if (!tmp)
		me->var_read = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	**ft_strsplit_var(char *line, int nbr)
{
	char	**str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	str = (char**)ft_memalloc(sizeof(char*) * (nbr + 1));
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		k = i;
		while (line[i] && line[i] != ' ' && j != nbr - 1)
			i++;
		if (line[i] == '\0' || j == nbr - 1)
		{
			str[j] = ft_strdup(&line[k]);
			break ;
		}
		else
			str[j++] = ft_strndup(&line[k], i - k);
		line[i] ? i++ : 0;
	}
	return (str);
}

void	ft_read(t_me *me, t_cmd *cmd)
{
	int		i;
	int		nbr;
	char	*line;
	char	**str;
	char	*s;

	i = 1;
	line = NULL;
	s = NULL;
	nbr = ft_tablen(cmd->args) - 1;
	get_next_line(0, &line);
	str = ft_strsplit_var(line, nbr);
	while (i <= nbr)
	{
		if ((s = get_edt(me->e, cmd->args[i])))
		{
			free(s);
			env_modif(me->e, cmd->args[i], str[i - 1]);
		}
		else
			ft_push_read(me, cmd->args[i], str[i - 1]);
		i++;
	}
	free(line);
	tab_free(str);
}
