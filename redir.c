/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:47:49 by aderose           #+#    #+#             */
/*   Updated: 2021/12/17 17:18:33 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_next_redir(t_list *node)
{
	t_token	*tk_next;

	tk_next = get_next_token(node);
	if (!node || !node->next)
		return (0);
	if (tk_next && ((tk_next->type == TK_IN_REDIR)
			|| (tk_next->type == TK_OUT_REDIR)
			|| (tk_next->type == TK_OUT_DREDIR)
			|| (tk_next->type == TK_HERE_DOC)))
		return (1);
	return (0);
}

char	*redir_heredoc(t_list *node, char *err_msg_fd, int *redir_in_done)
{
	t_token	*tk;
	int		fd;

	tk = (t_token *)node->content;
	fd = open(tk->value, O_RDONLY);
	if (fd == -1)
	{
		err_msg_fd = "Error: no such file or directory in_redir";
		return (err_msg_fd);
	}
	if (check_next_redir(node))
		close(fd);
	else
	{
		*redir_in_done = 1;
		if (dup2(fd, STDIN_FILENO) < 0)
			ft_error(&node, "fatal");
	}
	close(fd);
	return (err_msg_fd);
}

char	*redir_in(t_list *node, char *err_msg_fd, int *redir_in_done)
{
	t_token	*tk;
	int		fd;

	tk = (t_token *)node->content;
	fd = open(tk->value, O_RDONLY);
	if (fd == -1)
	{
		err_msg_fd = "Error: no such file or directory in_redir";
		return (err_msg_fd);
	}
	if (check_next_redir(node))
		close(fd);
	else
	{
		*redir_in_done = 1;
		if (dup2(fd, STDIN_FILENO) < 0)
			ft_error(&node, "fatal");
	}
	close(fd);
	return (err_msg_fd);
}

char	*redir_out(t_list *node, char *err_msg_fd, int *redir_out_done)
{
	t_token	*tk;
	int		fd;

	tk = (t_token *)node->content;
	fd = open(tk->value, O_RDWR | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		err_msg_fd = "Error: no such file or directory out_redir";
		return (err_msg_fd);
	}
	if (check_next_redir(node))
		close(fd);
	else
	{
		*redir_out_done = 1;
		if (dup2(fd, STDOUT_FILENO) < 0)
			ft_error(&node, "fatal");
	}
	close(fd);
	return (err_msg_fd);
}

char	*redir_append(t_list *node, char *err_msg_fd, int *redir_out_done)
{
	t_token	*tk;
	int		fd;

	tk = (t_token *)node->content;
	fd = open(tk->value, O_APPEND | O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		err_msg_fd = "Error: no such file or directory out_dredir";
		return (err_msg_fd);
	}
	if (check_next_redir(node))
		close(fd);
	else
	{
		*redir_out_done = 1;
		if (dup2(fd, STDOUT_FILENO) < 0)
			ft_error(&node, "fatal");
	}
	close(fd);
	return (err_msg_fd);
}
