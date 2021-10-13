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

t_node	*nodelast(t_node *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

t_node	*new_node(t_cmd *cmd)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->next = NULL;
	node->back = NULL;
	return (node);
}

void	rewind_node(t_node **node)
{
	if (!*node)
		return ;
	while (*node && (*node)->back)
		*node = (*node)->back;
}

void	clearnodes(t_node *node)
{
	clearnodes(node->next);
	if (node)
	{
		clearcmds(&node->cmd);
		free(node);
		node = NULL;
	}
}

void	nodeadd_back(t_node **anode, t_cmd *cmd)
{
	t_node	*node;
	t_node	*new;

	new = new_node(cmd);
	if (!new)
		return ;
	if (!*anode)
	{
		*anode = new;
		return ;
	}
	node = nodelast(*anode);
	node->next = new;
	new->back = node;
}
