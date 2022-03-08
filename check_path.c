/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:31:29 by aderose           #+#    #+#             */
/*   Updated: 2021/12/15 14:10:23 by jdidier          ###   ########.fr       */
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

int	check_access(char *path, char *next_path, char **mycmd)
{
	char	*new_cmd;
	char	*cur_path;

	if (next_path)
		cur_path = ft_substr(path, 0, next_path - path - 1);
	else
		cur_path = ft_strdup(path);
	new_cmd = joinpath(cur_path, *mycmd);
	if (access(new_cmd, X_OK | F_OK) == 0)
	{
		ft_free(mycmd);
		*mycmd = ft_strdup(new_cmd);
		ft_free(&cur_path);
		ft_free(&new_cmd);
		return (1);
	}
	ft_free(&cur_path);
	ft_free(&new_cmd);
	return (0);
}

int	check_path(t_msh *msh, char **mycmd)
{
	char	*path;
	char	*next_path;
	int		ret;

	path = NULL;
	next_path = NULL;
	ret = 0;
	path = get_env_value("PATH", msh->myenv, msh);
	if (!path)
		return (0);
	while (path && !ret)
	{
		next_path = ft_strchr(path, ':');
		if (next_path)
			next_path++;
		ret = check_access(path, next_path, mycmd);
		path = next_path;
	}
	return (ret);
}
