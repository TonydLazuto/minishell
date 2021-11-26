/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                         :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:26:44 by aderose           #+#    #+#             */
/*   Updated: 2021/10/13 21:26:54 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_builtin(t_node *node)
{
	if (!node->cmd.arg[0])
		return (0);
	else if (my_strncmp(node->cmd.arg[0], "cd") == 0)
		ft_cd(node);
	else if (my_strncmp(node->cmd.arg[0], "echo") == 0)
		ft_echo(node);
	else if (my_strncmp(node->cmd.arg[0], "pwd") == 0)
		ft_pwd(node);
	else if (my_strncmp(node->cmd.arg[0], "env") == 0)
		ft_env(node);
	else if (my_strncmp(node->cmd.arg[0], "export") == 0)
		ft_export(node);
	else if (my_strncmp(node->cmd.arg[0], "unset") == 0)
		ft_unset(node);
	else if (my_strncmp(node->cmd.arg[0], "exit") == 0)
		ft_exit(node);
	else
		return (0);
	return (1);
}

void	child_node(t_node *node, char **envp)
{
	if ((node->type == NODE_OUT_REDIR
			|| node->type == NODE_OUT_DREDIR))
		return ;
	if (node->type == NODE_IN_REDIR)
		child_in_redir(node);
	if (node->next && node->next->type == NODE_OUT_REDIR)
		child_out_redir(node);
	if (node->next && node->next->type == NODE_OUT_DREDIR)
		child_append(node);
	if (check_both_pipe_cmd(node))
		child_pipe(node);
	if (check_pipe(node))
		if (!check_cmd(node))
			return ;
	printf("|%s|\n", node->cmd.arg[0]);
	if (launch_builtin(node) == 0 || node->type == NODE_CMD)
	{
		if (node->cmd.arg[0][0] != '/')
			check_relatif_path(node, &node->cmd.arg[0]);
		if (execve(node->cmd.arg[0], node->cmd.arg, envp) == -1)
			ft_error(node, "error: execve()");
	}
}

void	parent_node(t_node *node)
{
	if (check_both_pipe_cmd(node))
		parent_pipe(node);
}

void	exec_cmd(t_node *node, char **envp)
{
	pid_t	pid;
	int		status;

	if (check_both_pipe_cmd(node))
		if (pipe(node->cmd.pipefd) == -1)
			ft_error(node, "error : pipe()");
	if (check_without_fork(node))
		child_node(node, envp);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_error(node, "error : fork()");
		if (pid == 0)
			child_node(node, envp);
		else
		{
			waitpid(pid, &status, WNOHANG);
			if (WIFEXITED(status) && (!node->back
					|| (node->back && node->back->type != NODE_PIPE)))
				node->cmd.exit_status = WEXITSTATUS(status);
			parent_node(node);
		}
	}
}
