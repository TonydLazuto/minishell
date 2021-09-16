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

t_node	*push_right(t_node *node, t_info info)
{
	t_node *elet;

	elet = new_node(info);
	if (!elet)
		return (NULL);
	if (!node)
		return (elet);
	node->right = elet;
	elet->parent = node;
	return (node);
}

t_node	*push_left(t_node *node, t_info info)
{
	t_node *elet;

	elet = new_node(info);
	if (!elet)
		return (NULL);
	if (!node)
		return (elet);
	node->left = elet;
	elet->parent = node;
	return (node);
}

t_node	*push_parent(t_node *left, t_node *right, t_info info)
{
	t_node	*elet;

	elet = new_node(info);
	if (!elet)
		return (NULL);
	elet->left = left;
	elet->right = right;
	if (left)
		left->parent = elet;
	if (right)
		right->parent = elet;
	return (elet);
}

/*
t_node	*pop_node(t_node *node, t_node *elet)
{
	t_node	*right_child;
	t_node	*left_child;
	t_node	*parent;

	if (!node)
		return (NULL);
	if (!elet)
		return (node);
	free(node);
	node = NULL;
	return (node);
}
*/