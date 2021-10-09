/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:44:35 by aderose           #+#    #+#             */
/*   Updated: 2021/09/16 10:44:41 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*lastnode(t_node *node)
{
	if (!node)
		return (NULL);
	while (node->right)
		node = node->right;
	return (node);
}