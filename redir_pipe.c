/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:57:47 by aderose           #+#    #+#             */
/*   Updated: 2021/11/20 13:31:45 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_pipe(t_astnode *node)
{
	if (node->right && node->right->type == NODE_PIPE)
	{
		if (dup2(node->cmd.pipefd[1], STDOUT_FILENO) < 0)
			ft_error(node, "error : dup2()");
	}
	if (node->parent && node->parent->type == NODE_PIPE)
	{
		if (dup2(node->parent->parent->cmd.pipefd[0], STDIN_FILENO) < 0)
			ft_error(node, "error : dup2()");
	}
	if ((node->right && node->right->type == NODE_PIPE)
		|| (node->parent && node->parent->type == NODE_PIPE))
	{
		close(node->cmd.pipefd[1]);
		close(node->cmd.pipefd[0]);
	}
}

void	parent_pipe(t_astnode *node)
{
	if ((node->right && node->right->type == NODE_PIPE)
		|| (node->parent && node->parent->type == NODE_PIPE))
	{
		close(node->cmd.pipefd[1]);
		if (node->parent && node->parent->type == NODE_PIPE)
		{
			close(node->parent->parent->cmd.pipefd[0]);
			if (!node->right || (node->right && node->right->type != NODE_PIPE))
				close(node->cmd.pipefd[0]);
		}
	}
}