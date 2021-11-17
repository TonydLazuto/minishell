/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:26:44 by aderose           #+#    #+#             */
/*   Updated: 2021/10/13 21:26:54 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bis.h"

void	child_node(t_astnode *node, char **env)
{
	if (node->type == PIPE
		|| (node->parent && node->parent->type == PIPE))
		child_pipe(node);
	if (node->type == REDIR_OUT)
		child_redi(node);
	if (node->parent && node->parent->type == REDIR_OUT)
		return ;
	if (check_builtin(node, env) == 0)
	{
		if (execve(node->cmd.arg[0], node->cmd.arg, env) == -1)
			ft_exit(node, "error: execve()");
	}
}

void	parent_node(t_astnode *node)
{
	if (node->type == PIPE
		|| (node->parent && node->parent->type == PIPE))
		parent_pipe(node);
}

void	exec_node(t_astnode *node, char **env)
{
	pid_t	pid;
	int		status;

	if (node->type == PIPE
		|| (node->parent && node->parent->type == PIPE))
	{
		if (pipe(node->cmd.pipefd) == -1)
			ft_exit(node, "error : pipe()");
	}
	if ((!node->parent || (node->parent && node->parent->type == END))
		&& node->type == END)
		child_node(node, env);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_exit(node, "error : fork()");
		if (pid == 0)
			child_node(node, env);
		else
		{
			parent_astnode(node);
			waitpid(pid, &status, 0);
		}
	}
}
