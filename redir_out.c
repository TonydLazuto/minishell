/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:47:49 by aderose           #+#    #+#             */
/*   Updated: 2021/10/11 17:31:38 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * BE CAREFUL 
 * Simple redirection do not replace all content
 * by the previous command
 * instead, copy the content of the command
 * and keep the rest of the content of the file
 */
void	child_out_redir(t_astnode *node)
{
	int	fd;

	if (!node->right->right)
		ft_error(node, "output redirection nowhere");
	fd = open(node->right->right->cmd.arg[0], O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		ft_error(node, "error : open()");
	if (node->cmd.arg[0] != NULL)
	{
		if (dup2(fd, 1) < 0)
			ft_error(node, "error : fatal");
	}
	close(fd);
}

void	child_append(t_astnode *node)
{
	int	fd;

	if (!node->right->right)
		ft_error(node, "output redirection nowhere");
	fd = open(node->right->right->cmd.arg[0], O_APPEND | O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		ft_error(node, "error : open()");
	if (node->cmd.arg[0] != NULL)
	{
		if (dup2(fd, 1) < 0)
			ft_error(node, "error : fatal");
	}
	close(fd);
}
