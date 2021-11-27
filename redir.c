/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:47:49 by aderose           #+#    #+#             */
/*   Updated: 2021/11/25 16:55:38 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_out_redir(t_node *node)
{
	if (node->next->cmd.len != 1)
		ft_error(node, "error : wrong nb_args NODE_REDIR");
	node->cmd.fd= open(node->next->cmd.arg[0], O_RDWR | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	// printf("fd |%d|\n", node->next->cmd.fd);
	if (node->cmd.fd == -1)
		ft_error(node, "error : open()");
	if (dup2(node->cmd.fd, 1) < 0)
		ft_error(node, "error : fatal");
	if (node->next->type != NODE_OUT_REDIR)
		close(node->cmd.fd);
}

void	child_in_redir(t_node *node)
{
	if (node->cmd.len != 1)
		ft_error(node, "error : wrong nb_args NODE_REDIR");
	node->cmd.fd= open(node->cmd.arg[0], O_RDWR);
	if (node->cmd.fd == -1)
		ft_error(node, "error : open()");
	if (dup2(node->cmd.fd, 0) < 0)
		ft_error(node, "error : fatal");
	close(node->cmd.fd);
}

void	child_append(t_node *node)
{
	if (node->next->cmd.len != 1)
		ft_error(node, "error : wrong nb_args NODE_DREDIR");
	node->cmd.fd= open(node->next->cmd.arg[0], O_APPEND | O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (node->cmd.fd == -1)
		ft_error(node, "error : open()");
	if (dup2(node->cmd.fd, 1) < 0)
		ft_error(node, "error : fatal");
	close(node->cmd.fd);
}
