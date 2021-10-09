/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:25:16 by aderose           #+#    #+#             */
/*   Updated: 2021/10/07 17:25:18 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	change_dir(t_node *node)
{
	int	i;
	int	ret;

	i = 0;
	while (node->cmd.arg[i])
		i++;
	if (i != 2 || !node->cmd.arg[1])
		ft_exit(node, "error: cd: bad arguments", 0);
	ret = chdir(node->cmd.arg[1]);
	if (ret == -1)
		ft_exit(node, "error: cd: cannot change directory to path_to_change", 0);
}

void	make_cmd(t_node *node, char **env)
{
	pid_t	pid;
	int		status;

	if (node->type == TYPE_PIPE ||
		(node->parent && node->parent->type == TYPE_PIPE))
	{
		if (pipe(node->pipefd) == -1)
			ft_exit(node, "error : fatal", 0);
	}
	pid = fork();
	if (pid < 0)
		ft_exit(node, "error : fatal", 0);
	if (pid == 0)
	{
		if (node->type == TYPE_PIPE && node->right)
		{
			if (dup2(node->pipefd[1], STDOUT_FILENO) < 0)
				ft_exit(node, "error : fatal", 0);
		}
		if (node->parent && node->parent->type == TYPE_PIPE)
		{
			if (dup2(node->parent->pipefd[0], STDIN_FILENO) < 0)
				ft_exit(node, "error : fatal", 0);
		}
		if (node->type == TYPE_PIPE ||
			(node->parent && node->parent->type == TYPE_PIPE))
		{
			close(node->pipefd[1]);
			close(node->pipefd[0]);
		}
		if (execve(node->cmd.arg[0], node->cmd.arg, env) == -1)
			ft_exit(node, "error: cannot execute ", 1);
	}
	else
	{
		if (node->type == TYPE_PIPE ||
			(node->parent && node->parent->type == TYPE_PIPE))
		{
			close(node->pipefd[1]);
			if (node->type != TYPE_PIPE)
			{
				close(node->parent->pipefd[0]);
				if (!node->right || (node->right && node->right->type != TYPE_PIPE))
					close(node->pipefd[0]);
			}
		}
		waitpid(pid, &status, 0);
	}
}
