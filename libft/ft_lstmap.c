/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 21:15:36 by jdidier           #+#    #+#             */
/*   Updated: 2021/10/14 10:24:46 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	const t_list	*lstp;
	void			*is_success;
	t_list			*ret;
	t_list			*new;

	lstp = lst;
	ret = NULL;
	new = NULL;
	while (lstp)
	{
		is_success = f(lstp->content);
		if (is_success)
		{
			new = ft_lstnew(is_success);
			if (!new)
			{
				ft_lstclear(&lst, del);
				return (NULL);
			}
			ft_lstadd_back(&ret, new);
		}
		lstp = lstp->next;
	}
	return (ret);
}
