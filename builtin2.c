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
 * Un nom de variable d'env peut être composé de lettres,
 * de chiffres et d'underscores.
 * Mais il ne doit pas commencer par un chiffre. 
 * 
 * key = value
 * 
 * stocker tous les export dans une liste chainee ?
 * 
 */

void	mini_parse_export(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!ft_isalpha(cmd->arg[1][0]))
		ft_exit(cmd, "error: first character of argument is not alpha");
	while (cmd->arg[1][i] && cmd->arg[1][i] != '=')
	{
		if (!ft_isalnum(cmd->arg[1][i]) && cmd->arg[1][i] != '_')
			ft_exit(cmd, "export: invalid character in var env");
		i++;
	}
	if (cmd->arg[1][i] != '=')
		ft_exit(cmd, "export: invalid argument");
	i++;
	if (cmd->arg[1][i] == '\0')
		ft_exit(cmd, "export: not initialized");
	while (cmd->arg[1][i])
	{
		if (!ft_isascii(cmd->arg[1][i]))
			ft_exit(cmd, "export: env value is not ascii");
		i++;
	}
}

void	ft_export(t_cmd *cmd, char **env)
{
	(void)env;
	if (!cmd->arg[1])
		ft_exit(cmd, "export: too few arguments");
	if (cmd->arg[2])
		ft_exit(cmd, "export: too many arguments");
	mini_parse_export(cmd);

}

