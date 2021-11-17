/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:57:47 by aderose           #+#    #+#             */
/*   Updated: 2021/10/11 14:43:55 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bis.h"

void	child_pipe(t_astnode *node)
{
	if (node->right && node->right->type == TK_PIPE)
	{
		if (dup2(node->cmd.pipefd[1], STDOUT_FILENO) < 0)
			ft_exit(node, "error : dup2()");
	}
	if (node->parent && node->parent->type == TK_PIPE)
	{
		if (dup2(node->parent->parent->cmd.pipefd[0], STDIN_FILENO) < 0)
			ft_exit(node, "error : dup2()");
	}
	if ((node->right && node->right->type == TK_PIPE)
		|| (node->parent && node->parent->type == TK_PIPE))
	{
		close(node->cmd.pipefd[1]);
		close(node->cmd.pipefd[0]);
	}
}

void	parent_pipe(t_astnode *node)
{
	if ((node->right && node->right->type == TK_PIPE)
		|| (node->parent && node->parent->type == TK_PIPE))
	{
		close(node->cmd.pipefd[1]);
		if (node->parent && node->parent->type == TK_PIPE)
		{
			close(node->parent->parent->cmd.pipefd[0]);
			if (!node->right || (node->right && node->right->type != TK_PIPE))
				close(node->cmd.pipefd[0]);
		}
	}
}