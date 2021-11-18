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

void    ft_env(t_astnode *node)
{
	t_env	*env;

	printf("%s\n", (*node->env)->name);

//	env = (*node->env);
	if (node->cmd.arg[1])
		ft_exit(node, "env: too many arguments");
	while (env)
	{
		ft_putstr_fd(env->name, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(env->value, 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
}

void	mini_parse_export(t_astnode *node)
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
void	split_export(t_astnode *node, char **key, char **val)
{
	size_t			len;
	unsigned int	start;

	len = 1;
	while (node->cmd.arg[1][len] && node->cmd.arg[1][len] != '=')
		len++;
	start = len + 1;
	*key = ft_substr(node->cmd.arg[1], 0, len);
	if (!*key)
		ft_exit(node, "export: malloc");
	while (node->cmd.arg[1][len])
		len++;
	*val = ft_substr(node->cmd.arg[1], start, len);
	if (!*val)
		ft_exit(node, "export: malloc");
}
/*
int		is_exist_in_env(char **env)
{
	return (1);
}

int		ft_setenv(char *name, char *value, char **env)
{
	if (is_exist(name))
		set_name();
}

int		ft_unsetenv(char *name, char **env)
{
	if (!is_exist(name))
		return (1);
}
*/
void	ft_export(t_astnode *node)
{
	char *key;
	char *val;

	key = NULL;
	val = NULL;
	// if (!node->cmd.arg[1])
	// 	; //export ==> env with no args + declare
	if (node->cmd.arg[2])
		ft_exit(node, "export: too many arguments");
	mini_parse_export(node);
	split_export(node, &key, &val);

	// if (val)
	// 	;//modify env variable
	// else
	// 	;//add new env variable
	free(key);
	free(val);
}

