/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:16:56 by aderose           #+#    #+#             */
/*   Updated: 2021/09/06 19:33:33 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*elmt;

	if (!lst || !f)
		return (NULL);
	elmt = ft_lstnew(f(lst->content));
	if (!elmt)
		return (NULL);
	lst = lst->next;
	first = elmt;
	while (lst)
	{
		elmt->next = ft_lstnew(f(lst->content));
		if (!(elmt->next))
		{
			ft_lstclear(&first, del);
			return (first);
		}
		elmt = elmt->next;
		lst = lst->next;
	}
	elmt = NULL;
	return (first);
}
