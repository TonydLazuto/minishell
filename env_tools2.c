/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:44:47 by aderose           #+#    #+#             */
/*   Updated: 2021/12/22 19:09:21 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_env_line(char *line, char *new_line)
{
	char	*tmp;

	tmp = line;
	line = ft_strdup(new_line);
	free(tmp);
	return (line);
}

char	*join_env_value(char *line, char *name, char *value)
{
	char	*tmp;

	tmp = line;
	line = ft_strjoin(name, value);
	free(tmp);
	return (line);
}

void	free_myenv(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			free(env[i]);
			env[i] = NULL;
			i++;
		}
		free(env);
		env = NULL;
	}
}

char	*get_env_value(char *name, char **env, t_msh *msh)
{
	int		line;
	char	*value;

	line = get_env_line(env, name);
	if (line == -1)
		return (NULL);
	value = ft_strchr(msh->myenv[line], '=');
	value++;
	return (value);
}
