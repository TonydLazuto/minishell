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

void	child_pipe(t_cmd *cmd)
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