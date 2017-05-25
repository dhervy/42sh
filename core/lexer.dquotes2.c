/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.dquotes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertojo <tbertojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 02:06:39 by tbertojo          #+#    #+#             */
/*   Updated: 2017/05/03 02:08:38 by tbertojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	check_last_quote_loop(char *s, int *j, int *q)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && nescape(s, i) && *q == 0)
		{
			*q = 1;
			*j = i;
			i++;
		}
		if (*q == 1)
			if (s[i] == s[*j] && nescape(s, i))
			{
				*q = 0;
				*j = 0;
			}
	}
}

int		check_last_quote(t_edl *edl, char **qtype, char *s)
{
	int		q;
	int		j;
	char	*tmp;

	q = 0;
	j = 0;
	tmp = NULL;
	check_last_quote_loop(s, &j, &q);
	if (q)
	{
		*qtype ? free(*qtype) : 0;
		*qtype = ft_strndup(&s[j], 1);
		edl->type = (!ft_strcmp(*qtype, "\'") ? SQUOT : DQUOT);
		s ? free(s) : 0;
		return (0);
	}
	else
	{
		s ? free(s) : 0;
		return (1);
	}
}

char	*last_one(t_me *me, t_edl *edl, char *s, char **qtype)
{
	int i;

	i = -1;
	while (s && s[++i] && s[i] != **qtype)
		;
	if (s[i] && nescape(s, i) && check_last_quote(edl, qtype,\
		ft_strjoinfree(ft_strjoin(me->edl.line, edl->t), s, 1)))
		return (ft_strndup(s, i));
	return (0);
}

void	execute_qenter_do(t_me *me, t_edl *edl)
{
	int i;

	i = 0;
	while (i++ < (((edl->line ? (int)ft_strlen(edl->line) : 0)\
	- edl->spos - 6) / (me->width ? me->width : 1)) + 1)
		exec_mode(me, "do");
}

void	execute_qenter_init(t_me *me, t_edl *edl)
{
	mprompt(me, edl->type, 1);
	edl->line = 0;
	me->trees = 0;
	me->go = 1;
	edl->spos = 0;
	edl->pos.x = edl->prompt_size;
	edl->pos.y = 0;
}
