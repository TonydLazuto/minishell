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

void	child_pipe(t_node *node, char **env)
{
	if (node->cmd->type == PIPE && node->cmd->next)
	{
		if (dup2(node->cmd->pipefd[1], STDOUT_FILENO) < 0)
			ft_exit(node, "error : fatal");
	}
	if (node->cmd->back && node->cmd->back->type == PIPE)
	{
		if (dup2(node->cmd->back->pipefd[0], STDIN_FILENO) < 0)
			ft_exit(node, "error : fatal");
	}
	if (node->cmd->type == PIPE ||
		(node->cmd->back && node->cmd->back->type == PIPE))
	{
		close(node->cmd->pipefd[1]);
		close(node->cmd->pipefd[0]);
	}
	if (execve(node->cmd->arg[0], node->cmd->arg, env) == -1)
		ft_exit(node, "error: cannot execute ");
}

void	parent_pipe(t_node *node)
{
	if (node->cmd->type == PIPE
		|| (node->cmd->back && node->cmd->back->type == PIPE))
	{
		close(node->cmd->pipefd[1]);
		if (node->cmd->type != PIPE)
		{
			close(node->cmd->back->pipefd[0]);
			if (!node->cmd->next || (node->cmd->next && node->cmd->next->type != PIPE))
				close(node->cmd->pipefd[0]);
		}
	}
}

void	pipes(t_node *node, char **env)
{
	pid_t	pid;
	int		status;

	if (node->cmd->type == PIPE
		|| (node->cmd->back && node->cmd->back->type == PIPE))
	{
		if (pipe(node->cmd->pipefd) == -1)
			ft_exit(node, "error : fatal");
	}
	pid = fork();
	if (pid < 0)
		ft_exit(node, "error : fatal");
	if (pid == 0)
		child_pipe(node, env);
	else
	{
		parent_pipe(node);
		waitpid(pid, &status, 0);
	}
}
