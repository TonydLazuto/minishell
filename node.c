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

t_node	*new_node(enum e_ntype ntype)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->ntype = ntype;
	node->cmd.arg = NULL;
	node->parent = NULL;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

void	rewind_tree(t_node **node)
{
	if (!*node)
		return ;
	while (*node && (*node)->parent)
		*node = (*node)->parent;
}

void	clear_node(t_node *node)
{
	int	i;

	if (!node)
		return ;
	clear_node(node->right);
	clear_node(node->left);
	if (node)
	{
		if (node->ntype == CMD && node->cmd.arg)
		{
			i = 0;
			while (node->cmd.arg[i])
			{
				free(node->cmd.arg[i]);
				node->cmd.arg[i] = NULL;
				i++;
			}
			free(node->cmd.arg);
		}
		free(node);
		node = NULL;
	}
}

t_node	*push_right(t_node *parent, t_node *child_r)
{
	if (!child_r)
		return (NULL);
	if (!parent)
		return (child_r);
	child_r->parent = parent;
	parent->right = child_r;
	return (child_r);
}

t_node	*push_left(t_node *parent, t_node *child_l)
{
	if (!child_l)
		return (NULL);
	if (!parent)
		return (child_l);
	child_l->parent = parent;
	parent->left = child_l;
	return (child_l);
}
