/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:16:28 by aderose           #+#    #+#             */
/*   Updated: 2021/09/06 19:31:41 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*before;

	if (lst == NULL || !del)
		return ;
	tmp = lst;
	before = lst;
	while (tmp != lst)
	{
		before = tmp;
		tmp = tmp->next;
	}
	before->next = tmp->next;
	free(tmp);
	del(tmp->content);
}
