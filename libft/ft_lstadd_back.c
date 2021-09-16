/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:15:21 by aderose           #+#    #+#             */
/*   Updated: 2021/09/06 19:31:08 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*lst;

	if (new == NULL)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		new->next = NULL;
		return ;
	}
	lst = ft_lstlast(*alst);
	lst->next = new;
	new->next = NULL;
}
