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

void	child_node(t_astnode *node, char **envp)
{
	if ((node->right && node->right->type == TK_PIPE)
		|| (node->parent && node->parent->type == TK_PIPE))
		child_pipe(node);
	if (node->right && node->right->type == TK_OUT_REDIR)
		child_out_redi(node);
	if (node->parent && node->parent->type == TK_OUT_REDIR)
		return ;
	if (check_builtin(node) == 0)
	{
		if (execve(node->cmd.arg[0], node->cmd.arg, envp) == -1)
			ft_exit(node, "error: execve()");
	}
}

void	parent_node(t_astnode *node)
{
	if ((node->right && node->right->type == TK_PIPE)
		|| (node->parent && node->parent->type == TK_PIPE))
		parent_pipe(node);
}

//check_if_exec();

void	exec_cmd(t_astnode *node, char **envp)
{
	pid_t	pid;
	int		status;

	if ((node->right && node->right->type == TK_PIPE)
		|| (node->parent && node->parent->type == TK_PIPE))
	{
		if (pipe(node->cmd.pipefd) == -1)
			ft_exit(node, "error : pipe()");
	}
	/**
	 * Voir les conditioms pour entre dans le fork
	 * parce que si execve est lance et qu'il y a pas eu de fork() avant
	 * le programme s'arrete.
	 */
	if ((!node->parent || (node->parent && node->parent->type != TK_PIPE))
		&& (!node->right || (node->right && node->right->type != TK_PIPE)))
		child_node(node, envp);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_exit(node, "error : fork()");
		if (pid == 0)
			child_node(node, envp);
		else
		{
			parent_node(node);
			waitpid(pid, &status, 0);
		}
	}
}
