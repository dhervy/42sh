/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:47:48 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/02 16:21:48 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*cdel(char *s, int m)
{
	char	*new;
	int		i;

	if (!s)
		return (0);
	new = malloc(ft_strlen(s));
	i = -1;
	while (s[++i] && i < m)
		new[i] = s[i];
	while (s[++i])
		new[i - 1] = s[i];
	new[ft_strlen(s) - 1] = 0;
	free(s);
	return (new);
}

void	ctab_print(char **s)
{
	int i;

	i = -1;
	while (s[++i])
		ft_putendl(s[i]);
}

int		ft_sii(char *s, char *e)
{
	int	is;
	int	ie;

	is = -1;
	while (s[++is])
	{
		ie = 0;
		while (s[is + ie] && e[ie] && s[is + ie] == e[ie])
			++ie;
		if (!e[ie])
			return (1);
	}
	return (0);
}

char	*ssn(char *s, char *f)
{
	int		a;
	int		ta;
	int		b;

	a = -1;
	while (s[++a] && !(b = 0))
	{
		ta = a;
		while (s[a++] == f[b++])
			if (!f[b])
				return (&(s[ta]));
		a = ta;
	}
	return (NULL);
}

int		mlen(char *s, char a)
{
	int b;

	b = 0;
	while (s[b] && s[b] != a)
		b++;
	return (b ? b : ft_strlen(s));
}
