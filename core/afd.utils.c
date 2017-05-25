/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   afd.utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:18:43 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/06 10:38:11 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		verif_second(char *s, int *type, int *r)
{
	int	i;

	i = 1;
	*type = *s == '>' && *(s + 1) && *(s + 1) == '>' ? ADD : NONE;
	*s == '>' && *(s + 1) && *(s + 1) != '>' ? *type = OVER : 0;
	*s == '<' ? *type = CLOSE : 0;
	if (*type != NONE)
		s += (*type == ADD ? 2 : 1);
	else
		*r = 0;
	!*s ? *r = 0 : 0;
	if (s && *s == '&' && (++s))
		i = 0;
	!*s ? *r = 0 : 0;
	*s && !i && !ft_isdigit(*s) && *s != '-' ? *r = 0 : 0;
	!i && *s && *s == '-' ? *type = CLOSE : 0;
	return (1);
}

int		is_afd(char *s)
{
	int		type;
	int		r;

	r = 0;
	if (!ft_strcmp(s, "<<") || !ft_strcmp(s, ">>") || ft_strlen(s) < 2)
		return (0);
	if ((ft_strchr(s, '>') || ft_strchr(s, '<')) && (r = 1))
	{
		*s != '&' && !ft_isdigit(*s) &&
		*s != '>' && *s != '<' ? r = 0 : 0;
		if (*s == '&')
			++s;
		while (r && ft_isdigit(*s))
			++s;
		verif_second(s, &type, &r);
	}
	return (r);
}

int		prepare_afds(t_afd *list)
{
	t_afd	*c;

	if (!list)
		return (0);
	c = list;
	while (c && ft_strcmp(c->str, ";") &&
	ft_strcmp(c->str, "&&") && ft_strcmp(c->str, "||"))
	{
		if (c->i_file)
		{
			if (c->type == OVER &&
				(c->new = open(c->file_name, O_RDWR | O_TRUNC |\
					O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
				;
			if (c->type == ADD &&
				(c->new = open(c->file_name, O_RDWR | O_APPEND |\
					O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
				;
			if (c->new == -1)
				return (-1);
		}
		c = c->next;
	}
	return (1);
}

void	free_afds(t_afd *list)
{
	t_afd		*c;
	t_afd		*next;

	if (!list)
		return ;
	c = list;
	while (c && ft_strcmp(c->str, ";"))
	{
		next = c->next;
		free(c->str);
		c->file_name ? free(c->file_name) : 0;
		free(c);
		c = next;
	}
	if (c && !ft_strcmp(c->str, ";"))
	{
		c->file_name ? free(c->file_name) : 0;
		free(c->str);
		free(c);
	}
}
