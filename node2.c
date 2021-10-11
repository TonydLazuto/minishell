/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:44:35 by aderose           #+#    #+#             */
/*   Updated: 2021/10/11 14:46:37 by aderose          ###   ########.fr       */
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

t_node	*set_node_cmd(t_node *node, const char **arg, enum e_cmdtype type)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	node->cmd.arg = (char **)malloc(sizeof(char *) * (i + 1));
	if (!node->cmd.arg)
		ft_exit(node, "malloc node->cmd.arg");
	i = 0;
	while (arg[i])
	{
		node->cmd.arg[i] = ft_strdup(arg[i]);
		if (!node->cmd.arg[i])
			ft_exit(node, "malloc node->cmd.arg[i]");
		i++;
	}
	node->cmd.arg[i] = NULL;
	node->cmd.type = type;
	return (node);
}
