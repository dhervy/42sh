/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplet2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 21:55:18 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/01 21:55:30 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_auto	*ft_init_auto(char *name)
{
	t_auto	*new_auto;

	new_auto = (t_auto*)ft_memalloc(sizeof(t_auto));
	new_auto->value = ft_strdup(name);
	return (new_auto);
}

char	*ft_auto_get_string(char *str, int index)
{
	int		i;
	int		j;
	char	*string;

	if (index == 0)
		return (ft_strdup(""));
	i = index - 1;
	j = i;
	while (i > 0 && str[i] != ' ')
		i--;
	if (str[i] != ' ')
		string = ft_strndup(&str[i], (j - i) + 1);
	else
		string = ft_strndup(&str[i + 1], (j - i) + 1);
	return (string);
}

char	*ft_auto_get_path(char *string)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = -1;
	while (string[i])
	{
		if (string[i] == '/')
			j = i;
		i++;
	}
	if (j == -1)
	{
		path = ft_strdup("./");
	}
	else
	{
		path = ft_strndup(string, j + 1);
	}
	return (path);
}

char	*ft_auto_get_debut(char *string)
{
	int		i;
	char	*debut;

	i = ft_strlen(string);
	while (i > 0)
	{
		if (string[i] == '/')
			break ;
		i--;
	}
	if (i == 0 && string[i] != '/')
		i--;
	debut = ft_strdup(&string[i + 1]);
	return (debut);
}

int		ft_auto_cmp(char *cmp, char *name)
{
	int		i;

	i = 0;
	if (ft_strlen(name) < ft_strlen(cmp))
		return (0);
	while (cmp[i])
	{
		if (cmp[i] != name[i])
			return (0);
		i++;
	}
	return (1);
}
