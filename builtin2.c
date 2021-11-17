/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:54:22 by aderose           #+#    #+#             */
/*   Updated: 2021/11/12 13:54:23 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bis.h"
/**
 * name
 * A word consisting solely of letters, numbers,
 * and underscores, and beginning with a letter or underscore.
 * Names are used as shell variable and function names.
 * Also referred to as an identifier.
 * word
 * A sequence of characters treated as a unit by the shell.
 * Words may not include unquoted metacharacters. 
 * 
 * key = value
 * 
 */

void	mini_parse_export(t_astnode *node, char **key)
{
	int	i;

	i = 1;
	if (!ft_isalpha(node->cmd.arg[1][0]))
		ft_exit(node, "error: first character of argument is not alpha");
	while (node->cmd.arg[1][i] && node->cmd.arg[1][i] != '=')
	{
		if (!ft_isalnum(node->cmd.arg[1][i]) && node->cmd.arg[1][i] != '_')
			ft_exit(node, "export: invalid character in var env");
		i++;
	}
	if (node->cmd.arg[1][i] != '=')
		ft_exit(node, "export: invalid argument");
	*key = ft_substr(node->cmd.arg[1], 0, (size_t)i);
	if (!*key)
		ft_exit(node, "export: malloc");
	i++;
	if (node->cmd.arg[1][i] == '\0')
		ft_exit(node, "export: not initialized");
	while (node->cmd.arg[1][i])
	{
		if (!ft_isascii(node->cmd.arg[1][i]))
			ft_exit(node, "export: env value is not ascii");
		i++;
	}
}

void	ft_export(t_astnode *node, char **env)
{
	char *key;
	// char *val;

	(void)env;
	key = NULL;
	// val = NULL;
	if (!node->cmd.arg[1])
		ft_exit(node, "export: too few arguments");
	if (node->cmd.arg[2])
		ft_exit(node, "export: too many arguments");
	mini_parse_export(node, &key);
	// val = getenv(key);
	// if (val)
	// 	;//modify env variable
	// else
	// 	;//add new env variable
	free(key);
}

