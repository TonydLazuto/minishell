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
 * INFO
 * name
 * A word consisting solely of letters, numbers,
 * and underscores, and beginning with a letter or underscore.
 * Names are used as shell variable and function names.
 * Also referred to as an identifier.
 * word
 * A sequence of characters treated as a unit by the shell.
 * Words may not include unquoted metacharacters. 
 */

int	mini_parse_export2(t_node *node, int i, int *append)
{
	if (node->cmd.arg[1][i] == '+')
	{
		i++;
		if (node->cmd.arg[1][i] != '=')
			ft_error(node, "export: invalid argument");
		i++;
		*append = 1;
	}
	else if (node->cmd.arg[1][i] == '=')
		i++;
	else
		ft_error(node, "export: invalid argument");
	return (i);
}

void	mini_parse_export(t_node *node, int *append)
{
	int	i;

	i = 1;
	if (!ft_isalpha(node->cmd.arg[1][0]))
		ft_error(node, "error: first character of argument is not alpha");
	while (node->cmd.arg[1][i] && node->cmd.arg[1][i] != '='
			&& node->cmd.arg[1][i] != '+')
	{
		if (!ft_isalnum(node->cmd.arg[1][i]) && node->cmd.arg[1][i] != '_')
			ft_error(node, "export: invalid character in var env");
		i++;
	}
	if (!node->cmd.arg[1][i])
		return ;
	i = mini_parse_export2(node, i, append);
	if (node->cmd.arg[1][i - 1] != '=')
		ft_error(node, "export: invalid argument");
	if (node->cmd.arg[1][i] == '\0')
		ft_error(node, "export: not initialized");
	while (node->cmd.arg[1][i])
	{
		if (!ft_isascii(node->cmd.arg[1][i]))
			ft_error(node, "export: env value is not ascii");
		i++;
	}
}

void	ft_export(t_node *node)
{
	int	append;

	append = 0;
	node->cmd.exit_status = 0;
	if (node->cmd.len == 1)
	{
		export_no_args(node);
		return ;
	}
	if (node->cmd.len != 2)
		ft_error(node, "export: too many arguments");
	mini_parse_export(node, &append);
	if (append == 1)
		export_append(node);
	else
		export_normal(node);
}
