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
 * INFO
 * Tous les builtin doivent retourner une valeur
 * pour $?
 */

#include "minishell.h"

void	ft_unset(t_node *node)
{
	t_env	*elet;

	node->cmd.exit_status = 1;
	elet = node->cmd.env;
	if (!node->cmd.arg[1])
		return ;
	elet = get_env_by_name(node->cmd.env, node->cmd.arg[1]);
	if (elet)
		node->cmd.env = pop_env(node->cmd.env, elet->name);
	node->cmd.exit_status = 0;
}

int	check_dash_n(t_node *node)
{
	int	i;

	i = 2;
	if (my_strncmp(node->cmd.arg[1], "-n") == 0)
	{
		while (node->cmd.arg[1][i])
		{
			if (node->cmd.arg[1][i] != 'n')
				return (0);
			i++;
		}
		return (2);
	}
	return (1);
}

void	ft_echo(t_node *node)
{
	int	i;

	if (!node->cmd.arg[1])
		ft_putstr_fd("\n", 1);
	if (node->cmd.arg[1])
	{
		i = check_dash_n(node);
		if (i == 0)
			ft_error(node, "Error: echo -n + gibberish");
		if (node->cmd.arg[i])
			ft_putstr_fd(node->cmd.arg[i], 1);
		if (i == 1)
			ft_putstr_fd("\n", 1);
	}
}

void	ft_pwd(t_node *node)
{
	char	*buf;

	buf = NULL;
	if (node->cmd.arg[1])
		ft_error(node, "pwd: too many arguments");
	buf = getcwd(buf, 0);
	if (!buf)
		ft_error(node, "error: malloc PWD");
	ft_putendl_fd(buf, 1);
	ft_free(&buf);
}

void	ft_env(t_node *node)
{
	t_env	*env;

	env = node->cmd.env;
	if (node->cmd.arg[1])
		ft_error(node, "env: too many arguments");
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->name, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(env->value, 1);
			ft_putchar_fd('\n', 1);
		}
		env = env->next;
	}
}
