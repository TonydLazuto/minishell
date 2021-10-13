/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:47:49 by aderose           #+#    #+#             */
/*   Updated: 2021/10/11 17:31:38 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * 	if node->cmd->arg == NULL
 * 		child_stdin() //redirige sur STDIN
 */

void	append_args_to_file(t_node *node)
{
	int	fd;
	int	i;

	i = 1;
	fd = open(node->next->cmd->arg[0], O_APPEND);
	if (fd == -1)
		ft_exit(node, "error : fatal");
	while (node->next->cmd->arg[i])
	{
		write(fd, (void *)node->next->cmd->arg[i], ft_strlen(node->next->cmd->arg[i]));
		if (node->next->cmd->arg[i + 1])
			write(fd, " ", 1);
		i++;
	}
}

void	child_redi(t_node *node, char **env, int fd)
{
	if (node->cmd->arg != NULL)
	{
		if (dup2(node->cmd->pipefd[1], fd) < 0)
			ft_exit(node, "error : fatal");
	}
//	else if (node->cmd->arg == NULL)
//		child_stdin(node, env);
	close(node->cmd->pipefd[1]);
	close(node->cmd->pipefd[0]);
	if (execve(node->cmd->arg[0], node->cmd->arg, env) == -1)
		ft_exit(node, "error: cannot execve");
}

void	check_exceptions(t_node *node)
{
	if (!node->cmd->arg)
	{
		if (node->next && node->next->)
	}
}

void	output_redi(t_node *node, char **env)
{
	pid_t	pid;
	int		status;
	int		fd;

	if (!node->next)
 		ft_exit(node, "error after output redir");
	check_exceptions(node);
	if (node->cmd->type == OUTPUT_REDI)
	{
		if (pipe(node->cmd->pipefd) == -1)
			ft_exit(node, "error : fatal");
	}
	fd = open(node->next->cmd->arg[0], O_RDWR | O_CREAT);
	if (fd == -1)
		ft_exit(node, "error : fatal");
	pid = fork();
	if (pid < 0)
		ft_exit(node, "error : fatal");
	if (pid == 0)
		child_redi(node, env, fd);
	else
	{
		close(node->cmd->pipefd[1]);
		close(node->cmd->pipefd[0]);
		waitpid(pid, &status, 0);
	}
	close(fd);
	if (node->cmd->arg != NULL && node->next->cmd->arg[1] != NULL)
		append_args_to_file(node);
}
