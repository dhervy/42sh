/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edl.clipboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:46:47 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/06 11:48:03 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*msub_string(char *s, int start, int end)
{
	char *r;
	char *e;

	if (!s || (start <= 0 && end >= (int)ft_strlen(s)))
	{
		s ? free(s) : 0;
		return (0);
	}
	r = ft_strndup(s, start);
	e = ft_strdup(s + 1 + end);
	s ? free(s) : 0;
	return (join_free(r, e));
}

char	*cut_clipboard(t_edl *edl)
{
	if (edl->select[0] == -1 || edl->select[1] == -1)
		return (0);
	return (ft_strndup(edl->line + edl->select[0],
	1 + edl->select[1] - edl->select[0]));
}
