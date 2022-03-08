/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:29:26 by aderose           #+#    #+#             */
/*   Updated: 2021/12/22 16:14:35 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_add(char **env, char *str)
{
	char	**newenv;
	int		i;

	newenv = NULL;
	i = 0;
	while (env[i])
		i++;
	newenv = malloc(sizeof(char *) * (i + 2));
	if (!newenv)
		return (NULL);
	i = 0;
	while (env[i])
	{
		newenv[i] = ft_strdup(env[i]);
		free(env[i]);
		i++;
	}
	newenv[i] = ft_strdup(str);
	i++;
	newenv[i] = NULL;
	free(env);
	return (newenv);
}

char	**env_after_unset(char **env, int line)
{
	char	**newenv;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	newenv = malloc(sizeof(char *) * i);
	i = 0;
	while (env[j])
	{
		if (j != line)
			newenv[i] = ft_strdup(env[j]);
		else
			i--;
		i++;
		j++;
	}
	newenv[i] = NULL;
	return (newenv);
}

int	get_env_line(char **env, char *name)
{
	int		line;
	int		len;
	char	*s;

	line = 0;
	s = NULL;
	if (!env)
		return (-1);
	while (env[line])
	{
		len = 0;
		while (env[line][len] && env[line][len] != '=')
			len++;
		s = ft_substr(env[line], 0, len);
		if (ft_strlen(s) == ft_strlen(name)
			&& ft_strcmp(s, name) == 0)
		{
			ft_free(&s);
			return (line);
		}
		ft_free(&s);
		line++;
	}
	return (-1);
}

char	**env_cpy(char **envp)
{
	char	**env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}
