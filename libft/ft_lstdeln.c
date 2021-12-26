/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdeln.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:09:08 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/07 13:38:45 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdeln(t_list **lst, void (*del)(void*), size_t n)
{
	t_list	*tmp;

	size_t	i;
	i = 0;
	while (*lst && del && i < n)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
		i++;
	}
	return (*lst);
}