/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplet3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 21:55:47 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 21:55:58 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_push_auto(t_auto **lsauto, char *name)
{
	t_auto	*tmp;
	t_auto	*new_auto;

	tmp = *lsauto;
	while (tmp->next)
		tmp = tmp->next;
	new_auto = ft_init_auto(name);
	tmp->next = new_auto;
	tmp->next->prev = tmp;
}

int		ft_create_auto(t_auto **lsauto, char *path, char *debut)
{
	DIR				*rep;
	struct dirent	*fichier;

	if ((rep = opendir(path)) == NULL)
		return (0);
	while ((fichier = readdir(rep)) != NULL)
	{
		if (ft_auto_cmp(debut, fichier->d_name) && fichier->d_name[0] != '.')
		{
			if (!*lsauto)
			{
				*lsauto = ft_init_auto(fichier->d_name);
			}
			else
			{
				ft_push_auto(lsauto, fichier->d_name);
			}
		}
	}
	closedir(rep);
	if (!*lsauto)
		return (0);
	else
		return (1);
}

int		ft_auto_sizemax(t_auto **lsauto)
{
	t_auto	*tmp;
	int		sizemax;

	tmp = *lsauto;
	sizemax = 0;
	while (tmp)
	{
		if ((int)ft_strlen(tmp->value) > sizemax)
			sizemax = ft_strlen(tmp->value);
		tmp = tmp->next;
	}
	return (sizemax);
}

void	ft_count_column(t_me *me)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	me->width = w.ws_col;
	me->height = w.ws_row;
}

int		ft_auto_get_nbrline(t_auto **lsauto, int columnlist)
{
	t_auto	*tmp;
	int		i;
	int		nbr;

	i = 0;
	tmp = *lsauto;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	nbr = i / columnlist;
	if (i % columnlist > 0)
		nbr++;
	return (nbr);
}
