/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                              :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:34:50 by aderose           #+#    #+#             */
/*   Updated: 2021/10/12 16:35:02 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(char *arg[], int type, t_env *env)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->cmd.arg = arg;
	node->cmd.pipefd[0] = 0;
	node->cmd.pipefd[1] = 0;
	node->cmd.env = env;
	node->cmd.len = 0; // while arg[i]
	node->type = type;
	node->next = NULL;
	node->back = NULL;
	return (node);
}

t_node	*nodelast(t_node *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

void	clearnodes(t_node **node)
{
	t_node	*tmp;
	int		i;

	tmp = NULL;
	if (*node)
	{
		while (*node)
		{
			tmp = (*node)->next;
			if ((*node)->cmd.arg)
			{
				i = 0;
				while ((*node)->cmd.arg[i])
				{
					free((*node)->cmd.arg[i]);
					i++;
				}
				free((*node)->cmd.arg);
			}
			free(*node);
			*node = NULL;
			*node = tmp;
		}
	}
}

void	nodeadd_back(t_node **anode, char *arg[], int type, t_env *env)
{
	t_node	*node;
	t_node	*new;

	new = new_node(arg, type, env);
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
