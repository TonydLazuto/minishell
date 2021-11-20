/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:31:29 by aderose           #+#    #+#             */
/*   Updated: 2021/11/20 14:20:52 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*joinpath(char *s1, char *s2)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '/';
	i++;
	while (*s2)
	{
		str[i] = *s2++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	clear_paths(char **paths)
{
	int	i;

	i = 0;
	if (paths)
	{
		while (paths[i])
		{
			free(paths[i]);
			paths[i] = NULL;
			i++;
		}
		free(paths);
		paths = NULL;
	}
}

char	*check_access(char *cur_path, char *cmd)
{
	char	*new_cmd;

	new_cmd = joinpath(cur_path, cmd);
	if (access(new_cmd, X_OK | F_OK) == 0)
	{
		ft_free(&cmd);
		return (new_cmd);
	}
	ft_free(&new_cmd);
	return (NULL);
}

char	*check_relatif_path(t_astnode *node)
{
	t_env	*env;
	char	*new_cmd;
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	env = get_env_by_name(node->cmd.env, "PATH");
	if (!env)
		ft_error(node, "error: PATH env dosen't exist. \
			Cannot add relative path.");
	paths = ft_split(env->value, ':');
	if (!paths)
		ft_error(node, "error: malloc()");
	while (paths[i])
	{
		new_cmd = check_access(paths[i], node->cmd.arg[0]);
		if (new_cmd)
			break ;
		i++;
	}
	if (!new_cmd)
		new_cmd = node->cmd.arg[0];
	clear_paths(paths);
	return (new_cmd);
}
