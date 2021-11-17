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

void    ft_env(t_astnode *node, char **env)
{
    int	line;

	line = 0;
	if (node->cmd.arg[1])
		ft_exit(node, "env: too many arguments");
	while (env[line])
	{
		ft_putendl_fd(env[line], 1);
		line++;
	}
}

void	change_dir(t_astnode *node)
{
	int	i;
	int	ret;

	i = 0;
	while (node->cmd.arg[i])
		i++;
	if (i != 2 || !node->cmd.arg[1])
		ft_exit(node, "error: cd bad arguments");
	ret = chdir(node->cmd.arg[1]);
	if (ret == -1)
		ft_exit(node, "error: chdir");
}

void	ft_echo(t_astnode *node)
{
	if (!node->cmd.arg[1])
		ft_putstr_fd("\n", 1);
	if (node->cmd.arg[1])
	{
		if (ft_strcmp(node->cmd.arg[1], "-n") == 0)
		{
			if (node->cmd.arg[2])
				ft_putstr_fd(node->cmd.arg[2], 1);
			else
				return ; // rl_on_new_line()
		}
		else
			ft_putendl_fd(node->cmd.arg[1], 1);
	}
}

void	ft_pwd(t_astnode *node)
{
	char	*buf;

	buf = NULL;

	if (node->cmd.arg[1])
		ft_exit(node, "pwd: too many arguments");
	buf = getcwd(buf, 0);
	ft_putendl_fd(buf, 1);
}

int		check_builtin(t_astnode *node, char **env)
{
	if (!node->cmd.arg)
		return (0);
	else if (ft_strcmp(node->cmd.arg[0], "cd") == 0)
		change_dir(node);
	else if (ft_strcmp(node->cmd.arg[0], "echo") == 0)
		ft_echo(node);
	else if (ft_strcmp(node->cmd.arg[0], "pwd") == 0)
		ft_pwd(node);
	else if (ft_strcmp(node->cmd.arg[0], "env") == 0)
		ft_env(node, env);
	else if (ft_strcmp(node->cmd.arg[0], "export") == 0)
		ft_export(node, env);
	// else if (ft_strcmp(node->cmd.arg[0], "unset") == 0)
	// 	;
	// else if (ft_strcmp(node->cmd.arg[0], "exit") == 0)
	// 	;
	else
		return (0);
	return (1);
}