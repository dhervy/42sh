/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.p_ex4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertojo <tbertojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 02:51:49 by tbertojo          #+#    #+#             */
/*   Updated: 2017/05/03 15:16:01 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*find_same_hist_return1(t_me *me, t_hist *tmp, char *fin, int t)
{
	if (t == 0)
		return (ft_strjoinfree(ft_strdup(tmp->name), fin, 3));
	else if (t == 1)
		return (ft_strjoinfree(\
			find_last_param(me, ft_strdup(tmp->name)), fin, 3));
	else if (t == 2)
		return (ft_strjoinfree(find_param(me, ft_strdup(tmp->name)), fin, 3));
	return (NULL);
}

char	*find_same_hist(char *str, t_me *me, int t, int nb)
{
	t_hist	*tmp;
	char	*file;
	char	*fin;

	tmp = me->hi;
	find_cmp(&fin, &file, str);
	find_cmp_option(&t, &nb, &file, -1);
	if (tmp && file)
	{
		while (tmp && tmp->next && tmp->next->next)
			tmp = tmp->next;
		while (tmp && tmp->name && \
		ft_strncmp(tmp->name, file, ft_strlen(file)) != 0)
			tmp = tmp->prev;
		if (tmp)
		{
			free(file);
			if (t != 3)
				return (find_same_hist_return1(me, tmp, fin, t));
			return (find_same_hist_return2(me, tmp, fin, nb));
		}
	}
	fin ? free(fin) : 0;
	file ? free(file) : 0;
	return (NULL);
}

char	*remplace_line(t_me *me, int nb)
{
	t_hist *tmp;

	tmp = NULL;
	tmp = me->hi;
	if (tmp)
	{
		if (nb > 0)
			while (tmp && tmp->next && nb > (tmp->index + 1))
				tmp = tmp->next;
		else if (nb < 0)
		{
			nb = -nb;
			while (tmp && tmp->next)
				tmp = tmp->next;
			while (tmp && tmp->prev && nb)
			{
				tmp = tmp->prev;
				nb--;
			}
		}
		if (tmp->name)
			return (ft_strdup(tmp->name));
	}
	return (NULL);
}

void	remplace_last_hist(t_me *me, char *str)
{
	rm_last_elem_hist(me);
	push_hist(me, str);
}

char	*tab_to_str(char **tabb)
{
	char	*str;
	int		i;

	i = -1;
	str = NULL;
	while (tabb && tabb[++i])
		str = (str ? ft_strjoinfree(ft_strjoinfree(str, " ", 1), tabb[i], 1) :\
		ft_strdup(tabb[i]));
	return (str);
}
