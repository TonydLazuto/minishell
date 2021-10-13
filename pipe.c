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

void	child_pipe(t_cmd *cmd, char **env)
{
	if (cmd->type == PIPE && cmd->next)
	{
		if (dup2(cmd->pipefd[1], STDOUT_FILENO) < 0)
			ft_exit(cmd, "error : dup2()");
	}
	if (cmd->back && cmd->back->type == PIPE)
	{
		if (dup2(cmd->back->pipefd[0], STDIN_FILENO) < 0)
			ft_exit(cmd, "error : dup2()");
	}
	if (cmd->type == PIPE ||
		(cmd->back && cmd->back->type == PIPE))
	{
		close(cmd->pipefd[1]);
		close(cmd->pipefd[0]);
	}
	if (execve(cmd->arg[0], cmd->arg, env) == -1)
		ft_exit(cmd, "error: execve()");
}

void	parent_pipe(t_cmd *cmd)
{
	if (cmd->type == PIPE
		|| (cmd->back && cmd->back->type == PIPE))
	{
		close(cmd->pipefd[1]);
		if (cmd->back && cmd->back->type == PIPE)
		{
			close(cmd->back->pipefd[0]);
			if (!cmd->next || (cmd->next && cmd->next->type != PIPE))
				close(cmd->pipefd[0]);
		}
	}
}

void	pipes(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		status;

	if (cmd->type == PIPE
		|| (cmd->back && cmd->back->type == PIPE))
	{
		if (pipe(cmd->pipefd) == -1)
			ft_exit(cmd, "error : pipe()");
	}
	pid = fork();
	if (pid < 0)
		ft_exit(cmd, "error : fork()");
	if (pid == 0)
		child_pipe(cmd, env);
	else
	{
		parent_pipe(cmd);
		waitpid(pid, &status, 0);
	}
}
