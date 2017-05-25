/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:45:18 by vde-la-s          #+#    #+#             */
/*   Updated: 2015/12/01 14:13:45 by vde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *ne;

	ne = (t_list*)malloc(sizeof(t_list));
	if (!ne)
		return (NULL);
	ne->next = NULL;
	if (content)
	{
		if (!(ne->content = ft_memalloc(content_size)))
			return (NULL);
		ne->content_size = content_size;
		ft_memcpy(ne->content, content, content_size);
	}
	else
	{
		ne->content_size = 0;
		ne->content = NULL;
	}
	return (ne);
}
