/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 13:48:15 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/08 12:32:05 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	return_line(char *eol, char *s)
{
	if (!(*s = 0) && !eol)
		return (0);
	*eol++ = 0;
	ft_strcpy(s, eol);
	return (1);
}

static int	fill_line(char **line, char *buf)
{
	char *tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
	return (*line ? 1 : -1);
}

int			get_next_line(int const fd, char **line)
{
	static char s[BUFF_SIZE];
	char		buf[BUFF_SIZE + 1];
	char		*n;
	int			r;

	if (!line || fd < 0 || fd > 255 || BUFF_SIZE < 1)
		return (-1);
	if (!(*line = *s ? ft_strdup(s) : ft_strnew(1)))
		return (-1);
	while ((r = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[r] = 0;
		if (!fill_line(line, buf))
			return (-1);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	n = ft_strchr(*line, '\n');
	if (return_line(n, s) || ft_strlen(*line) || r > 0)
		return (1);
	return (!r ? 0 : -1);
}
