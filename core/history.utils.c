/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:50:22 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 02:35:13 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_strjoinfree(char const *s1, char const *s2, int i)
{
	char	*fre;
	char	*fre1;
	char	*str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return ((char*)s2);
	else if (s2 == NULL)
		return ((char*)s1);
	fre = (char*)s1;
	fre1 = (char*)s2;
	str = ft_strjoin(s1, s2);
	if (i == 1 || i == 3)
		free(fre);
	if (i == 2 || i == 3)
		free(fre1);
	return (str);
}

int		intlen(long int nbr)
{
	int		i;

	i = 1;
	if (nbr < 0)
		nbr = -nbr;
	while (nbr > 9)
	{
		nbr = (nbr / 10);
		i++;
	}
	return (i);
}

void	print_hist(t_me *me)
{
	t_hist *t;

	t = me->hi;
	while (t)
	{
		ft_putendl(t->name);
		t = t->next;
	}
}

int		push_hist(t_me *me, char *s)
{
	t_hist *new;
	t_hist *curs;

	if (!s || !(new = malloc(sizeof(t_hist))))
		return (0);
	new->next = 0;
	new->prev = 0;
	new->select = 0;
	new->inlist = 0;
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

t_hist	*get_hist(t_me *me, int i)
{
	t_hist *curs;
	t_hist *r;

	curs = me->hi;
	r = 0;
	while (curs)
	{
		if (curs->index == i)
			r = curs;
		curs = curs->next;
	}
	return (r);
}
