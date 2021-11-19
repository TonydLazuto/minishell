/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:27:23 by aderose           #+#    #+#             */
/*   Updated: 2021/11/18 11:27:24 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bis.h"

t_env	*new_env(char *name, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(*env));
	if (!env)
		return (NULL);
	env->name = name;
    env->value = value;
	env->back = NULL;
	env->next = NULL;
	return (env);
}

int		get_env_size(t_env *env)
{
	int		size;

	size = 0;
	if (env)
	{
		while (env)
		{
			size++;
			env = env->next;
		}
	}
	return (size);
}

t_env	*envlast(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

void	clear_env(t_env **env)
{
	t_env	*tmp;

	tmp = NULL;
	if (*env)
	{
		while (*env)
		{
			tmp = (*env)->next;
			if ((*env)->name)
				free((*env)->name);
            if ((*env)->value)
				free((*env)->value);
			free(*env);
			*env = NULL;
			*env = tmp;
		}
	}
}

void	envadd_back(t_env **aenv, char *name, char *value)
{
	t_env	*env;
	t_env	*new;

	new = new_env(name, value);
	if (!new)
		return ;
	if (!*aenv)
	{
		*aenv = new;
		return ;
	}
	env = envlast(*aenv);
	env->next = new;
	new->back = env;
}
