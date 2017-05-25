/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <dhervy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:13:13 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/21 22:10:32 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_auto_move_left(t_auto **lsauto)
{
	t_auto	*tmp;

	tmp = *lsauto;
	while (tmp && tmp->select == 0)
		tmp = tmp->next;
	tmp->select = 0;
	if (tmp->prev != NULL)
		tmp->prev->select = 1;
	else
	{
		tmp = *lsauto;
		while (tmp->next)
			tmp = tmp->next;
		tmp->select = 1;
	}
}

int		ft_auto_getkey(t_auto **lsauto, t_me *me, t_edl *edl)
{
	unsigned long	buf;

	buf = 0;
	while (buf != 10)
	{
		buf = 0;
		read(0, (char*)&buf, 8);
		if (buf == RIGHT || buf == TAB)
		{
			ft_auto_move_right(lsauto);
			ft_print_auto(lsauto, me, edl, 0);
		}
		else if (buf == LEFT)
		{
			ft_auto_move_left(lsauto);
			ft_print_auto(lsauto, me, edl, 0);
		}
		else if (ft_isascii(buf) && buf != 10)
			return (0);
	}
	return (1);
}

char	*ft_auto_getname(t_auto **lsauto, char *debut)
{
	t_auto	*tmp;
	char	*str;
	int		i;

	i = ft_strlen(debut);
	tmp = *lsauto;
	while (tmp && tmp->select == 0)
		tmp = tmp->next;
	str = ft_strdup(&tmp->value[i]);
	return (str);
}

char	*ft_auto_complet(char *str, t_me *me, t_edl *edl)
{
	char	*path;
	char	*debut;
	char	*string;
	char	*retour;
	t_auto	*lsauto;

	lsauto = NULL;
	retour = NULL;
	string = ft_auto_get_string(str, edl->spos);
	path = ft_auto_get_path(string);
	debut = ft_auto_get_debut(string);
	if (!ft_create_auto(&lsauto, path, debut))
	{
		ft_auto_free(&lsauto, string, path, debut);
		return (NULL);
	}
	lsauto->select = 1;
	ft_print_auto(&lsauto, me, edl, 0);
	if (ft_auto_getkey(&lsauto, me, edl))
		retour = ft_auto_getname(&lsauto, debut);
	ft_auto_free(&lsauto, string, path, debut);
	exec_mode(me, "cd");
	return (retour);
}

void	get_autocomplet(t_me *me, t_edl *edl)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	str = ft_auto_complet(edl->line, me, edl);
	if (!str)
		return ;
	while (i < (int)ft_strlen(str))
	{
		insert_key(me, edl, str[i]);
		i++;
	}
	free(str);
}
