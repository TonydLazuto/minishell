/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:34:50 by aderose           #+#    #+#             */
/*   Updated: 2021/10/12 16:35:02 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bis.h"

t_astnode	*new_node(char *arg[], int type, t_env *env)
{
	t_astnode	*node;

	node = (t_astnode *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->cmd.arg = arg;
	node->cmd.pipefd[0] = 0;
	node->cmd.pipefd[1] = 0;
	node->type = type;
	node->env = env;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}
t_astnode	*nodelast(t_astnode *node)
{
	if (!node)
		return (NULL);
	while (node->right)
		node = node->right;
	return (node);
}

void		clearnodes(t_astnode **node)
{
	t_astnode	*tmp;
	int		i;

	tmp = NULL;
	if (*node)
	{
		while (*node)
		{
			tmp = (*node)->right;
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

void		nodeadd_right(t_astnode **anode, char *arg[], int type, t_env *env)
{
	t_astnode	*node;
	t_astnode	*new;

	new = new_node(arg, type, env);
	if (!new)
		return ;
	if (!*anode)
	{
		*anode = new;
		return ;
	}
	node = nodelast(*anode);
	node->right = new;
	new->parent = node;
}
