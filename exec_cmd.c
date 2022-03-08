/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:26:44 by aderose           #+#    #+#             */
/*   Updated: 2021/12/19 11:40:54 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_msh *msh, char **env, int *i)
{
	t_token	*tk;

	tk = (t_token *)msh->node->content;
	msh->pid[*i] = fork();
	if (msh->pid[*i] < 0)
		ft_error_msh(msh, "fork().");
	if (msh->pid[*i] == 0)
	{
		if (check_pipe(msh->node))
			child_pipe(msh->node);
		if (tk->arg[0][0] != '/')
			check_path(msh, &tk->arg[0]);
		if (execve(tk->arg[0], tk->arg, env) == -1)
			ft_error_msh(msh, "command not found.");
	}
	else
	{
		signal(SIGINT, child_signal);
		signal(SIGQUIT, child_signal);
		if (check_pipe(msh->node))
			parent_pipe(msh->node);
	}
}

void	prep_exec(t_msh *msh, t_token *tk, int *i)
{
	if (check_pipe(msh->node))
		if (pipe(tk->pipefd) == -1)
			ft_error_msh(msh, "pipe().");
	if (is_builtin(tk))
		launch_builtin(msh);
	else if (tk->type == TK_CMD)
	{
		exec_cmd(msh, msh->myenv, i);
		(*i)++;
	}
}

char	*loop_run_exec(t_msh *msh, t_token *tk)
{
	char	*err_msg_fd;
	t_token	*tk_prev;
	int		i;

	i = 0;
	tk_prev = NULL;
	err_msg_fd = apply_redir(msh->node);
	while (msh->node)
	{
		tk = (t_token *)msh->node->content;
		tk_prev = get_prev_token(msh->node);
		if (msh->node->prev && tk_prev->type == TK_PIPE)
			err_msg_fd = apply_redir(msh->node);
		if (err_msg_fd)
			return (err_msg_fd);
		prep_exec(msh, tk, &i);
		if (tk->type == TK_PIPE || !msh->node->next)
		{
			unset_stdio(msh);
			set_stdio(msh);
		}
		msh->node = msh->node->next;
	}
	multiple_cmds(msh);
	return (err_msg_fd);
}

void	run_exec(t_msh *msh)
{
	t_token	*tk;
	char	*err_msg_fd;

	err_msg_fd = NULL;
	tk = NULL;
	if (msh->node)
		tk = (t_token *)msh->node->content;
	set_stdio(msh);
	get_tilde(msh);
	try_redirs(msh->node);
	init_pids_pipes(msh);
	err_msg_fd = loop_run_exec(msh, tk);
	if (err_msg_fd)
		ft_putendl_fd(err_msg_fd, 2);
	if (msh->pid)
	{
		free(msh->pid);
		msh->pid = NULL;
	}
	unset_stdio(msh);
}
