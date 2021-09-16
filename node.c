/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:43:44 by aderose           #+#    #+#             */
/*   Updated: 2021/09/16 10:44:18 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(t_info info)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	info.node_info = NULL;
	info.debug = NULL;

	node->parent = NULL;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

void	clear_node(t_node *node)
{
	if (!node)
		return ;
	clear_node(node->right);
	clear_node(node->left);

	free(node);
	node = NULL;
}