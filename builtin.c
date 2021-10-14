/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:55:56 by aderose           #+#    #+#             */
/*   Updated: 2021/10/11 14:48:49 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(t_cmd *cmd)
{
	int	i;
	int	ret;

	i = 0;
	while (cmd->arg[i])
		i++;
	if (i != 2 || !cmd->arg[1])
		ft_exit(cmd, "error: cd bad arguments");
	ret = chdir(cmd->arg[1]);
	if (ret == -1)
		ft_exit(cmd, "error: chdir");
}

void	ft_echo(t_cmd *cmd)
{
	cmd = cmd->next;
}

int		check_builtin(t_cmd *cmd, int is_builtin)
{
	if (strcmp(cmd->arg[0], "cd") == 0)
		change_dir(cmd);
	else if (strcmp(cmd->arg[0], "echo") == 0)
		ft_echo(cmd);
/*	else if (strcmp(cmd->arg[0], "pwd") == 0)
		;
	else if (strcmp(cmd->arg[0], "export") == 0)
		;
	else if (strcmp(cmd->arg[0], "unset") == 0)
		;
	else if (strcmp(cmd->arg[0], "env") == 0)
		;
	else if (strcmp(cmd->arg[0], "exit") == 0)
		;
*/	
	else
		is_builtin = 0;
	return (is_builtin);
}