/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 12:13:58 by aderose           #+#    #+#             */
/*   Updated: 2021/11/20 12:14:01 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_node *node)
{
	while (node->back)
		node = node->back;
	clearnodes(&node);
	exit(EXIT_SUCCESS);
}

void	translate_home(t_node *node)
{
	t_env	*elet;

	elet = get_env_by_name(node->cmd.env, "HOME");
	if (elet)
	{
		free(node->cmd.arg[1]);
		node->cmd.arg[1] = NULL;
		node->cmd.arg[1] = ft_strdup(elet->value);
		if (!node->cmd.arg[1])
			ft_error(node, "error: malloc HOME");
	}
	else
		ft_error(node, "error: HOME doesn't exist");
}

void	maj_pwd(t_node *node)
{
	t_env	*env_pwd;
	t_env	*env_oldpwd;
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (!buf)
		ft_error(node, "error: malloc oldpwd");
	env_pwd = get_env_by_name(node->cmd.env, "PWD");
	env_oldpwd = get_env_by_name(node->cmd.env, "OLDPWD");
	if (env_pwd && env_oldpwd)
	{
		free(env_oldpwd->value);
		env_oldpwd->value = ft_strdup(env_pwd->value);
		if (!env_oldpwd->value)
			ft_error(node, "error: malloc PWD");
	}
	if (env_pwd)
	{
		free(env_pwd->value);
		env_pwd->value = ft_strdup(buf);
		if (!env_pwd->value)
			ft_error(node, "error: malloc PWD");
	}
	ft_free(&buf);
}

void	ft_cd(t_node *node)
{
	node->cmd.exit_status = 1;
	if (node->cmd.len > 2)
		ft_error(node, "cd: too many arguments");
	if (!node->cmd.arg[1] || (node->cmd.arg[1]
			&& (node->cmd.arg[1][0] == '~'
			&& node->cmd.arg[1][0] == '\0')))
		translate_home(node);
	if (chdir(node->cmd.arg[1]) == -1)
		ft_error(node, "error: chdir");
	maj_pwd(node);
	node->cmd.exit_status = 0;
}
