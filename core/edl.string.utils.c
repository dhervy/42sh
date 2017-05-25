/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edl.string.utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:47:41 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/02 17:52:08 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	mprompt(t_me *me, int type, int ok)
{
	if (type == LINE)
		psc("sh -->  ", ok ? "38;5;82" : "38;5;160", 1);
	else if (type == HDOC)
		ft_putstr_fd("heredoc ", me->fd);
	else if (type == DQUOT)
		ft_putstr_fd("dquote> ", me->fd);
	else if (type == SQUOT)
		ft_putstr_fd("squote> ", me->fd);
	else if (type == BACKS)
		ft_putstr_fd("backsl> ", me->fd);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}

void	ft_putistr(char *s, int start)
{
	while (s[start])
		ft_putchar(s[start++]);
}

char	*add_key(char *r, char n, int i)
{
	char	*new;
	int		c;

	if (!r)
	{
		new = malloc(2);
		new[0] = n;
		new[1] = 0;
		return (new);
	}
	new = malloc(ft_strlen(r) + 2);
	c = -1;
	while (r[++c] && c < i)
		new[c] = r[c];
	new[c] = n;
	while (r[c])
	{
		new[c + 1] = r[c];
		++c;
	}
	new[c + 1] = 0;
	free(r);
	return (new);
}

char	*delete_key(char *r, int i)
{
	char	*new;
	int		c;

	if (!r)
		return (0);
	if (ft_strlen(r) <= 1)
	{
		free(r);
		return (0);
	}
	new = malloc(ft_strlen(r));
	new[ft_strlen(r) - 1] = 0;
	c = -1;
	while (r[++c] && c < i)
		new[c] = r[c];
	++c;
	while (r[c])
	{
		new[c - 1] = r[c];
		++c;
	}
	free(r);
	return (new);
}
