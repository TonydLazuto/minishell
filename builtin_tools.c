/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:34:41 by aderose           #+#    #+#             */
/*   Updated: 2021/12/17 13:34:42 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_builtin(t_list *node)
{
	t_token	*tk;
	t_token	*tk_b4_prev;
	t_token	*tk_prev;
	t_token	*tk_next;

	tk = (t_token *)node->content;
	tk_prev = get_prev_token(node);
	tk_next = get_next_token(node);
	tk_b4_prev = get_prev_token(node->prev);
	if (node->next && (tk_next->type == TK_PIPE))
	{
		if (dup2(tk->pipefd[1], STDOUT_FILENO) < 0)
			ft_error(&node, "dup2()");
	}
	if (node->prev && node->prev->prev && (tk_prev->type == TK_PIPE))
	{
		if (dup2(tk_b4_prev->pipefd[0], STDIN_FILENO) < 0)
			ft_error(&node, "dup2()");
	}
	close(tk->pipefd[1]);
}

void	launch_builtin(t_msh *msh)
{
	t_token	*tk;

	tk = (t_token *)msh->node->content;
	if (!tk->arg)
		return ;
	if (check_pipe(msh->node))
		pipe_builtin(msh->node);
	if (ft_strcmp(tk->arg[0], "cd") == 0)
		ft_cd(msh);
	else if (ft_strcmp(tk->arg[0], "echo") == 0)
		ft_echo(msh->node);
	else if (ft_strcmp(tk->arg[0], "pwd") == 0)
		ft_pwd(msh->node);
	else if (ft_strcmp(tk->arg[0], "env") == 0)
		ft_env(msh);
	else if (ft_strcmp(tk->arg[0], "export") == 0)
		ft_export(msh);
	else if (ft_strcmp(tk->arg[0], "unset") == 0)
		ft_unset(msh, tk);
	else if (ft_strcmp(tk->arg[0], "exit") == 0)
		ft_exit(msh);
}

int	is_builtin(t_token *tk)
{
	if (!tk || !tk->arg)
		return (0);
	if (ft_strcmp(tk->arg[0], "cd") == 0
		|| ft_strcmp(tk->arg[0], "echo") == 0
		|| ft_strcmp(tk->arg[0], "pwd") == 0
		|| ft_strcmp(tk->arg[0], "env") == 0
		|| ft_strcmp(tk->arg[0], "export") == 0
		|| ft_strcmp(tk->arg[0], "unset") == 0
		|| ft_strcmp(tk->arg[0], "exit") == 0)
		return (1);
	return (0);
}
