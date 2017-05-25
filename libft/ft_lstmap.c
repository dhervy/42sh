/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:45:18 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 14:17:49 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*tmp;
	t_list		*new;

	new = NULL;
	while (lst)
	{
		if (!new)
		{
			new = (*f)(lst);
			tmp = new;
			tmp->next = NULL;
		}
		else
		{
			tmp->next = f(lst);
			tmp = tmp->next;
			tmp->next = NULL;
		}
		lst = lst->next;
	}
	return (new);
}
