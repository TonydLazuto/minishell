/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:44:56 by aderose           #+#    #+#             */
/*   Updated: 2021/12/17 17:18:49 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_creates_close(t_token *tk)
{
	int	fd;

	if (tk->type == TK_IN_REDIR)
	{
		fd = open(tk->value, O_RDONLY);
		if (fd == -1)
			return (0);
		close(fd);
	}
	else if (tk->type == TK_OUT_REDIR || tk->type == TK_OUT_DREDIR)
	{
		if (tk->value && access(tk->value, F_OK) != 0)
		{
			fd = open(tk->value, O_RDWR | O_CREAT, 0644);
			if (fd == -1)
				return (0);
			close(fd);
		}
	}
	return (1);
}

void	try_redirs(t_list *node)
{
	t_list	*cpy;
	t_token	*tk;

	cpy = node;
	if (cpy)
		tk = (t_token *)cpy->content;
	while (cpy)
	{
		if ((tk->type == TK_IN_REDIR
				|| tk->type == TK_OUT_REDIR
				|| tk->type == TK_OUT_DREDIR)
			&& open_creates_close(tk) == 0)
			break ;
		cpy = cpy->next;
		if (cpy)
			tk = (t_token *)cpy->content;
	}
}

char	*apply_redir_in(t_list *cpy, char *err_msg_fd, int *redir_in_done)
{
	t_token	*tk;

	tk = NULL;
	if (cpy)
	{
		tk = (t_token *)cpy->content;
		if (tk->type == TK_IN_REDIR)
			err_msg_fd = redir_in(cpy, err_msg_fd, redir_in_done);
		else if (tk->type == TK_HERE_DOC)
		{
			err_msg_fd = redir_heredoc(cpy, err_msg_fd, redir_in_done);
		}
	}
	return (err_msg_fd);
}

char	*apply_redir_out(t_list *cpy, char *err_msg_fd, int *redir_out_done)
{
	t_token	*tk;

	tk = NULL;
	if (cpy)
	{
		tk = (t_token *)cpy->content;
		if (tk->type == TK_OUT_REDIR)
			err_msg_fd = redir_out(cpy, err_msg_fd, redir_out_done);
		else if (tk->type == TK_OUT_DREDIR)
			err_msg_fd = redir_append(cpy, err_msg_fd, redir_out_done);
	}
	return (err_msg_fd);
}

char	*apply_redir(t_list *node)
{
	char	*err_msg_fd;
	int		redir_in_done;
	int		redir_out_done;
	t_list	*cpy_in;
	t_list	*cpy_out;

	cpy_in = node;
	cpy_out = node;
	err_msg_fd = NULL;
	redir_in_done = 0;
	redir_out_done = 0;
	while (cpy_in && ((t_token *)cpy_in->content)->type != TK_PIPE
		&& !err_msg_fd)
	{
		err_msg_fd = apply_redir_in(cpy_in, err_msg_fd, &redir_in_done);
		cpy_in = cpy_in->next;
	}
	while (cpy_out && ((t_token *)cpy_out->content)->type != TK_PIPE
		&& !err_msg_fd)
	{
		err_msg_fd = apply_redir_out(cpy_out, err_msg_fd, &redir_out_done);
		cpy_out = cpy_out->next;
	}
	return (err_msg_fd);
}
