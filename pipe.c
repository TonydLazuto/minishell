/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:57:47 by aderose           #+#    #+#             */
/*   Updated: 2021/11/25 16:55:57 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_pipe(t_node *node)
{
	if (node->next && node->next->type == NODE_PIPE)
	{
		if (dup2(node->cmd.pipefd[1], STDOUT_FILENO) < 0)
			ft_error(node, "error : dup2()");
	}
	if (node->back && node->back->type == NODE_PIPE)
	{
		if (dup2(node->back->back->cmd.pipefd[0], STDIN_FILENO) < 0)
			ft_error(node, "error : dup2()");
	}
	if (check_both_pipe_cmd(node))
	{
		close(node->cmd.pipefd[1]);
		close(node->cmd.pipefd[0]);
	}
}

void	parent_pipe(t_node *node)
{
	if (check_both_pipe_cmd(node))
	{
		close(node->cmd.pipefd[1]);
		if (node->back && node->back->type == NODE_PIPE)
		{
			if (node->back->back)
				close(node->back->back->cmd.pipefd[0]);
			if (!node->next || (node->next && node->next->type != NODE_PIPE))
				close(node->cmd.pipefd[0]);
		}
	}
}
