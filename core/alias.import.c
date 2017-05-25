/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.import.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 16:15:48 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/04 14:31:10 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*hist_val(char *l)
{
	int		i;

	i = -1;
	if (ft_strlen(l) < 2)
		return (0);
	l += 2;
	while (l[++i] && ft_isdigit(l[i]))
		;
	if (ft_strlen(&(l[i])) < 3)
		return (0);
	return (l[i + 3] ? l + i + 3 : 0);
}

void	fill_zsh_history_config(t_me *me, int fd)
{
	char	*line;
	int		i;

	line = 0;
	i = 0;
	while (get_next_line(fd, &line) && ++i)
	{
		push_hist(me, hist_val(line));
		free(line);
	}
	line ? free(line) : 0;
}

void	load_hist(t_me *me, char *line)
{
	char	*file;
	int		fd;

	return ;
	if ((file = ft_strdup(&(line[ft_strlen("zsh_hist=")]))))
	{
		if (access(file, F_OK))
		{
			ft_putendl("Unable to find history file");
			free(file);
			return ;
		}
		if ((fd = open(file, O_RDONLY)) == -1)
			ft_putendl("Unable to open history file");
		else
		{
			fill_zsh_history_config(me, fd);
			close(fd);
		}
		free(file);
	}
}

void	fill_alias_tab(t_me *me, int fd)
{
	char	*line;

	line = 0;
	while (get_next_line(fd, &line))
	{
		if (str_headmatch(line, "zsh_hist=") && ft_strlen(line) > 10)
			load_hist(me, line);
		else
			me->alias = tab_add(me->alias, line);
		free(line);
	}
	line ? free(line) : 0;
}

void	import_config(t_me *me)
{
	int		fd;

	me->alias = 0;
	if (access("config.21sh", F_OK))
	{
		ft_putendl("Unable to find config file");
		return ;
	}
	if ((fd = open("config.21sh", O_RDONLY)) == -1)
		ft_putendl("Unable to open config file");
	else
	{
		fill_alias_tab(me, fd);
		close(fd);
	}
}
