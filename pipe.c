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

#include "minishell.h"

void	child_handle(t_node *node, char **env)
{
	if (node->cmd.type == PIPE && node->right)
	{
		if (dup2(node->cmd.pipefd[1], STDOUT_FILENO) < 0)
			ft_exit(node, "error : fatal");
	}
	if (node->parent && node->parent->cmd.type == PIPE)
	{
		if (dup2(node->parent->cmd.pipefd[0], STDIN_FILENO) < 0)
			ft_exit(node, "error : fatal");
	}
	if (node->cmd.type == PIPE
		|| (node->parent && node->parent->cmd.type == PIPE))
	{
		close(node->cmd.pipefd[1]);
		close(node->cmd.pipefd[0]);
	}
	if (execve(node->cmd.arg[0], node->cmd.arg, env) == -1)
		ft_exit(node, "error: cannot execve");
}

void	parent_handle(t_node *node)
{
	if (node->cmd.type == PIPE
		|| (node->parent && node->parent->cmd.type == PIPE))
	{
		close(node->cmd.pipefd[1]);
		if (node->cmd.type != PIPE)
		{
			close(node->parent->cmd.pipefd[0]);
			if (!node->right || (node->right && node->right->cmd.type != PIPE))
				close(node->cmd.pipefd[0]);
		}
	}
}

void	pipes(t_node *node, char **env)
{
	pid_t	pid;
	int		status;

	if (node->cmd.type == PIPE
		|| (node->parent && node->parent->cmd.type == PIPE))
	{
		if (pipe(node->cmd.pipefd) == -1)
			ft_exit(node, "error : fatal");
	}
	pid = fork();
	if (pid < 0)
		ft_exit(node, "error : fatal");
	if (pid == 0)
		child_handle(node, env);
	else
	{
		parent_handle(node);
		waitpid(pid, &status, 0);
	}
}
