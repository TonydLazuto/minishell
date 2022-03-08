/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 20:05:15 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/01 20:25:30 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (!new)
	{
		
	}
	last = ft_lstlast(*alst);
	if (*alst)
	{
		last->next = new;
		new->prev = last;
	}
	else
		*alst = new;
}
