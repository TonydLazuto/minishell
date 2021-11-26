/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:10:35 by aderose           #+#    #+#             */
/*   Updated: 2021/11/26 19:10:37 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_node *node)
{
	if (!node->cmd.arg[0])
		return (0);
	if (my_strncmp(node->cmd.arg[0], "cd") == 0
		|| my_strncmp(node->cmd.arg[0], "echo") == 0
		|| my_strncmp(node->cmd.arg[0], "pwd") == 0
		|| my_strncmp(node->cmd.arg[0], "env") == 0
		|| my_strncmp(node->cmd.arg[0], "export") == 0
		|| my_strncmp(node->cmd.arg[0], "unset") == 0
		|| my_strncmp(node->cmd.arg[0], "exit") == 0)
		return (1);
	return (0);
}

int	check_both_pipe_cmd(t_node *node)
{
	if ((node->type == NODE_CMD
			&& (node->next && node->next->type == NODE_PIPE))
		|| ((node->back && node->back->type == NODE_PIPE)
			&& node->back->back->type == NODE_CMD))
		return (1);
	return (0);
}

int	check_pipe(t_node *node)
{
	if ((node->next && node->next->type == NODE_PIPE)
		|| (node->back && node->back->type == NODE_PIPE))
		return (1);
	return (0);
}

int	check_cmd(t_node *node)
{
	if (node->type == NODE_CMD
		&& node->back->back->type == NODE_CMD)
		return (1);
	return (0);
}

int	check_without_fork(t_node *node)
{
	if ((!node->back || (node->back && node->back->type != NODE_PIPE))
		&& (!node->next || (node->next && node->next->type != NODE_PIPE))
		&& is_builtin(node))
		return (1);
	return (0);
}
