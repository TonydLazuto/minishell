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

int		launch_builtin(t_astnode *node)
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
	// else if (my_strncmp(node->cmd.arg[0], "exit") == 0)
	// 	ft_exit(node);
	else
		return (0);
	return (1);
}

void	child_node(t_astnode *node, char **envp)
{
	if ((node->right && node->right->type == NODE_PIPE)
		|| (node->parent && node->parent->type == NODE_PIPE))
		child_pipe(node);
	if (node->right && node->right->type == NODE_OUT_REDIR)
		child_out_redi(node);
	if (node->parent && node->parent->type == NODE_OUT_REDIR)
		return ;
	if (launch_builtin(node) == 0)
	{
		if (execve(node->cmd.arg[0], node->cmd.arg, envp) == -1)
			ft_error(node, "error: execve()");
	}
}

void	parent_node(t_astnode *node)
{
	if ((node->right && node->right->type == NODE_PIPE)
		|| (node->parent && node->parent->type == NODE_PIPE))
		parent_pipe(node);
}

int		check_without_fork(t_astnode *node)
{
	if ((!node->parent || (node->parent && node->parent->type != NODE_PIPE))
		&& (!node->right || (node->right && node->right->type != NODE_PIPE))
		&& is_builtin(node))
		return (1);
	return (0);
}

void	exec_cmd(t_astnode *node, char **envp)
{
	pid_t	pid;
	int		status;

	if ((node->right && node->right->type == NODE_PIPE)
		|| (node->parent && node->parent->type == NODE_PIPE))
	{
		if (pipe(node->cmd.pipefd) == -1)
			ft_error(node, "error : pipe()");
	}
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
			parent_node(node);
			waitpid(pid, &status, 0);
		}
	}
}
