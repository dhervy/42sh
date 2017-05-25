/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:37:38 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/03/07 14:10:25 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_token(char *s)
{
	char	r;

	r = !ft_strcmp(s, "|") ? T_PIPE : T_CMD;
	r = !ft_strcmp(s, ";") ? T_SCL : r;
	r = !ft_strcmp(s, ">") ? T_SRR : r;
	r = !ft_strcmp(s, ">>") ? T_DRR : r;
	r = !ft_strcmp(s, "<<") ? T_DLR : r;
	r = !ft_strcmp(s, "<") ? T_SLR : r;
	r = !ft_strcmp(s, "&&") ? T_AND : r;
	r = !ft_strcmp(s, "||") ? T_OR : r;
	return (r);
}
