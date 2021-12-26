/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:57:47 by aderose           #+#    #+#             */
/*   Updated: 2021/12/08 13:57:15 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pids_pipes(t_msh *msh)
{
	t_list	*cpy;
	t_token	*tk;

	cpy = msh->node;
	msh->nb_cmds = 0;
	tk = NULL;
	while (cpy)
	{
		tk = (t_token *)cpy->content;
		if (!is_builtin(tk) && tk->type == TK_CMD)
			msh->nb_cmds++;
		cpy = cpy->next;
	}
	msh->pid = malloc(sizeof(pid_t) * (msh->nb_cmds + 1));
	msh->pid[msh->nb_cmds + 1] = 0;
	if (!msh->pid)
		ft_error_msh(msh, "malloc pids.");
}

void	multiple_cmds(t_msh *msh)
{
	int	status;
	int	i;

	i = 0;
	while (i < msh->nb_cmds)
	{
		waitpid(msh->pid[i], &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	child_pipe(t_list *node)
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
	close(tk->pipefd[0]);
	close(tk->pipefd[1]);
}

void	parent_pipe(t_list *node)
{
	t_token	*tk;
	t_token	*tk_b4_prev;
	t_token	*tk_prev;
	t_token	*tk_next;

	tk = (t_token *)node->content;
	tk_prev = get_prev_token(node);
	tk_next = get_next_token(node);
	tk_b4_prev = get_prev_token(node->prev);
	close(tk->pipefd[1]);
	if (node->prev && tk_prev->type == TK_PIPE)
	{
		if (node->prev->prev)
			close(tk_b4_prev->pipefd[0]);
		if (!node->next || (node->next && tk_next->type != TK_PIPE))
			close(tk->pipefd[0]);
	}
}
