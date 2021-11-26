/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:06:33 by aderose           #+#    #+#             */
/*   Updated: 2021/11/17 19:06:36 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_elet(t_env *elet)
{
	if (elet->name)
	{
		free(elet->name);
		elet->name = NULL;
	}
	if (elet->value)
	{
		free(elet->value);
		elet->value = NULL;
	}
	free(elet);
	elet = NULL;
}

t_env	*pop_env(t_env *env, char *name)
{
	t_env	*del_elet;
	t_env	*before;
	t_env	*after;

	del_elet = get_env_by_name(env, name);
	before = del_elet->back;
	after = del_elet->next;
	if (after)
		after->back = before;
	if (before)
		before->next = after;
	free_env_elet(del_elet);
	if (after)
		env = after;
	else if (before)
		env = before;
	else
		env = NULL;
	if (env)
		while (env->back)
			env = env->back;
	return (env);
}

t_env	*get_env_by_name(t_env *env, char *name)
{
	t_env	*elet;

	elet = env;
	while (elet)
	{
		if (ft_strlen(name) == ft_strlen(elet->name)
			&& my_strncmp(elet->name, name) == 0)
			return (elet);
		elet = elet->next;
	}
	return (NULL);
}

t_env	*parse_line_env(t_env *env, char *envp)
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

t_env	*get_linked_list(char **envp)
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
