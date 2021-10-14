/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:26:44 by aderose           #+#    #+#             */
/*   Updated: 2021/10/13 21:26:54 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_cmd(t_cmd *cmd, char **env)
{
	if (cmd->type == PIPE
		|| (cmd->back && cmd->back->type == PIPE))
		child_pipe(cmd);
	if (cmd->type == REDIR_OUT)
		child_redi(cmd);
	if (cmd->back && cmd->back->type == REDIR_OUT)
		return ;
	if (check_builtin(cmd) == 0)
	{
		if (execve(cmd->arg[0], cmd->arg, env) == -1)
			ft_exit(cmd, "error: execve()");
	}
}

void	parent_cmd(t_cmd *cmd)
{
	if (cmd->type == PIPE
		|| (cmd->back && cmd->back->type == PIPE))
		parent_pipe(cmd);
}

void	exec_cmd(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		status;

	if (cmd->type == PIPE
		|| (cmd->back && cmd->back->type == PIPE))
	{
		if (pipe(cmd->pipefd) == -1)
			ft_exit(cmd, "error : pipe()");
	}
	if ((!cmd->back || (cmd->back && cmd->back->type == END))
		&& cmd->type == END)
		child_cmd(cmd, env);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_exit(cmd, "error : fork()");
		if (pid == 0)
			child_cmd(cmd, env);
		else
		{
			parent_cmd(cmd);
			waitpid(pid, &status, 0);
		}
	}
}
