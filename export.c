/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:11:54 by aderose           #+#    #+#             */
/*   Updated: 2021/11/19 19:11:55 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 */

void	mini_parse_export(t_astnode *node)
{
	int	i;

	i = 1;
	if (!ft_isalpha(node->cmd.arg[1][0]))
		ft_error(node, "error: first character of argument is not alpha");
	while (node->cmd.arg[1][i] && node->cmd.arg[1][i] != '=')
	{
		if (!ft_isalnum(node->cmd.arg[1][i]) && node->cmd.arg[1][i] != '_')
			ft_error(node, "export: invalid character in var env");
		i++;
	}
	if (!node->cmd.arg[1][i])
		return ;
	if (node->cmd.arg[1][i] != '=')
		ft_error(node, "export: invalid argument");
	i++;
	if (node->cmd.arg[1][i] == '\0')
		ft_error(node, "export: not initialized");
	while (node->cmd.arg[1][i])
	{
		if (!ft_isascii(node->cmd.arg[1][i]))
			ft_error(node, "export: env value is not ascii");
		i++;
	}
}

void	split_key_val(t_astnode *node, char **key, char **val)
{
	size_t			len;
	unsigned int	start;

	len = 1;
	while (node->cmd.arg[1][len] && node->cmd.arg[1][len] != '=')
		len++;
	start = len + 1;
	*key = ft_substr(node->cmd.arg[1], 0, len);
	if (!*key)
		ft_error(node, "export: malloc");
	if (!node->cmd.arg[1][len])
		return ;
	while (node->cmd.arg[1][len])
		len++;
	*val = ft_substr(node->cmd.arg[1], start, len);
	if (!*val)
		ft_error(node, "export: malloc");
}

void	ft_export(t_astnode *node)
{
	char	*name;
	char 	*val;
	t_env	*elet;

	name = NULL;
	val = NULL;
	if (!node->cmd.arg[1])
	{
	 	export_no_args(node);
		return ;
	}
	if (node->cmd.arg[2])
		ft_error(node, "export: too many arguments");
	mini_parse_export(node);
	split_key_val(node, &name, &val);
	elet = get_env_by_name(node->cmd.env, name);
	if (elet)
	{
		free(elet->value);
		elet->value = ft_strdup(val);
	}
	else
		envadd_back(&node->cmd.env, name, val);
}
