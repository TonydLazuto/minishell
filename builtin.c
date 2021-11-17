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

int		check_dash_n(t_astnode *node)
{
	int i;

	i = 2;
	if (ft_strcmp(node->cmd.arg[1], "-n") == 0)
	{
		while (node->cmd.arg[1][i])
		{
			if (node->cmd.arg[1][i] != 'n')
				return (0);
			i++;
		}
	}
	return (1);
}

void	ft_echo(t_astnode *node)
{
	int	i;

	i = 1;
	if (!node->cmd.arg[1])
		ft_putstr_fd("\n", 1);
	if (node->cmd.arg[1])
	{
		if (check_dash_n(node))
		{
			if (node->cmd.arg[2])
				ft_putstr_fd(node->cmd.arg[2], 1);
			else
				return ; // rl_on_new_line()
		}
		else
		{
			while (node->cmd.arg[i])
			{
				ft_putstr_fd(node->cmd.arg[i], 1);
				i++;
			}
			ft_putstr_fd("\n", 1);
		}
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

int		check_builtin(t_astnode *node)
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
		ft_env(node);
	else if (ft_strcmp(node->cmd.arg[0], "export") == 0)
		ft_export(node);
	// else if (ft_strcmp(node->cmd.arg[0], "unset") == 0)
	// 	;
	// else if (ft_strcmp(node->cmd.arg[0], "exit") == 0)
	// 	;
	else
		return (0);
	return (1);
}