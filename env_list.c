/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:06:33 by aderose           #+#    #+#             */
/*   Updated: 2021/11/18 15:52:01 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bis.h"

t_env   *get_env_by_name(t_env *env, char *name)
{
	t_env	*elet;

	elet = env;
	while (elet)
	{
		if (ft_strcmp(elet->name, name) == 0)
			return (elet);
		elet = elet->next;
	}
	return (elet);
}

t_env   *parse_line_env(t_env *env, char *envp)
{
	char			*name;
	char			*value;
	size_t			j;
	unsigned int	start;

	j = 0;
	start = (unsigned int)j;
	value = NULL;
	while (envp[j] != '=')
		j++;
	name = ft_substr(envp, start, j);
	if (!name)
		return (NULL);
	start = (unsigned int)j + 1;
	while (envp[j])
		j++;
	value = ft_substr(envp, start, j);
	if (!value)
		return (NULL);
	envadd_back(&env, name, value);
	return (env);
}

t_env   *get_linked_list(char **envp)
{
	t_env	*env;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		env = parse_line_env(env, envp[i]);
		if (!env)
			return (NULL);
		i++;
	}
	return (env);
}
