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

#include "minishell_bis.h"

void	child_redi(t_cmd *cmd)
{
	int		file;

	if (!cmd->next)
 		ft_exit(cmd, "output redirection nulle part");
	file = open(cmd->next->arg[0], O_RDWR | O_CREAT,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (file == -1)
		ft_exit(cmd, "error : open()");
	if (cmd->arg != NULL)
	{
		if (dup2(file, 1) < 0)
			ft_exit(cmd, "error : fatal");	
	}
	close(file);
}
