/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:20:26 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/04/04 15:39:22 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	count_size_core(const char *str, int *i, int *size)
{
	if (str[(*i)] == '\"' && nescape((char*)str, *i))
	{
		(*size) += 2;
		while (str[++(*i)] && str[(*i)] != '\"')
			++(*size);
		str[(*i)] ? ++(*i) : 0;
	}
	else if (str[(*i)] == '\'' && nescape((char*)str, *i))
	{
		(*size) += 2;
		while (str[++(*i)] && str[(*i)] != '\'')
			++(*size);
		str[(*i)] ? ++(*i) : 0;
	}
	else
	{
		++(*size);
		++(*i);
	}
}

int		count_size(char const *str, int i, char c)
{
	int size;

	size = 0;
	if (str)
	{
		while (str[i] && (str[i] != c ||
			(str[i] == c && !nescape((char*)str, i))))
		{
			count_size_core((char*)str, &i, &size);
			if (!str || !str[i])
				break ;
		}
		size++;
		return (size);
	}
	return (0);
}
