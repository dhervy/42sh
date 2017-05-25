/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertojo <tbertojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 02:26:42 by tbertojo          #+#    #+#             */
/*   Updated: 2017/05/03 02:27:16 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*find_hist_file(t_me *me)
{
	char *name;
	char *tmp;

	if ((name = get_edt(me->e, "HOME")) == NULL)
	{
		ft_putendl("no Home history fail.");
		return (NULL);
	}
	tmp = ft_strjoin(name, "/.42sh_history");
	free(name);
	return (tmp);
}

void	history_w(t_me *me, char *name, int i)
{
	t_hist	*tmp;
	int		fd;

	tmp = me->hi;
	if (name == NULL)
	{
		i = 1;
		if ((name = find_hist_file(me)) == NULL)
			return ;
	}
	if ((fd = open(name, O_WRONLY | O_CREAT, 0644)) == -1)
	{
		ft_putendl("history error : invalid fd.");
		if (i == 1)
			free(name);
		return ;
	}
	while (tmp)
	{
		ft_putendl_fd(tmp->name, fd);
		tmp = tmp->next;
	}
	close(fd);
	if (name && i == 1)
		free(name);
}

void	history_a(t_me *me, char *name, int i)
{
	char	*tmp;
	int		fd;

	fd = 0;
	if (!name)
		return ;
	if (name[0] != '/' && i == 0)
		tmp = ft_strjoin("./", name);
	else
		tmp = name;
	if ((fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
	{
		ft_putendl("history error : invalid fd.");
		i == 1 ? free(name) : free(tmp);
		return ;
	}
	affi_history(me, -1, fd, 0);
	i == 1 ? free(name) : free(tmp);
	close(fd);
}

int		push_hist2(t_me *me, char *s)
{
	t_hist *new;
	t_hist *curs;

	if (!s || !(new = malloc(sizeof(t_hist))))
		return (0);
	new->next = 0;
	new->prev = 0;
	new->select = 0;
	new->inlist = 1;
	new->index = 0;
	new->name = ft_strdup(s);
	curs = me->hi;
	if (!curs)
		me->hi = new;
	else
	{
		new->index = 1;
		while (curs->next && ++(new->index))
			curs = curs->next;
		curs->next = new;
		new->prev = curs;
	}
	me->l = new;
	return (1);
}

void	history_r(t_me *me, char *name, int i)
{
	char	*str;
	char	*tmp;
	int		fd;

	fd = 0;
	str = NULL;
	if (!name)
		return ;
	tmp = ((name[0] != '/' && i == 0) ? ft_strjoin("./", name) : name);
	if ((fd = open(tmp, O_RDONLY)) == -1)
	{
		ft_putendl("error : no history file.");
		i > 0 ? free(name) : free(tmp);
		return ;
	}
	while (get_next_line(fd, &str))
	{
		i == 3 ? push_hist2(me, str) : push_hist(me, str);
		str ? free(str) : 0;
	}
	str ? free(str) : 0;
	i > 0 ? free(name) : free(tmp);
	close(fd);
}
