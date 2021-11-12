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

/**
 * Tous les builtin doivent retourner une valeur
 * pour $?
 */

#include "minishell_bis.h"

void    ft_env(t_cmd *cmd, char **env)
{
    int	line;

	line = 0;
	if (cmd->arg[1])
		ft_exit(cmd, "env: too many arguments");
	while (env[line])
	{
		ft_putendl_fd(env[line], 1);
		line++;
	}
}

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
	if (!cmd->arg[1])
		ft_putstr_fd("\n", 1);
	if (cmd->arg[1])
	{
		if (ft_strcmp(cmd->arg[1], "-n") == 0)
		{
			if (cmd->arg[2])
				ft_putstr_fd(cmd->arg[2], 1);
			else
				return ; // rl_on_new_line()
		}
		else
			ft_putendl_fd(cmd->arg[1], 1);
	}
}

void	ft_pwd(t_cmd *cmd)
{
	char	*buf;

	buf = NULL;

	if (cmd->arg[1])
		ft_exit(cmd, "pwd: too many arguments");
	buf = getcwd(buf, 0);
	ft_putendl_fd(buf, 1);
}

int		check_builtin(t_cmd *cmd, char **env)
{
	if (!cmd->arg)
		return (0);
	else if (ft_strcmp(cmd->arg[0], "cd") == 0)
		change_dir(cmd);
	else if (ft_strcmp(cmd->arg[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		ft_pwd(cmd);
	else if (ft_strcmp(cmd->arg[0], "env") == 0)
		ft_env(cmd, env);
	else if (ft_strcmp(cmd->arg[0], "export") == 0)
		ft_export(cmd, env);
	// else if (ft_strcmp(cmd->arg[0], "unset") == 0)
	// 	;
	else if (ft_strcmp(cmd->arg[0], "exit") == 0)
		;

	else
		return (0);
	return (1);
}