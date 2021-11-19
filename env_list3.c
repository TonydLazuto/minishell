/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:10:39 by aderose           #+#    #+#             */
/*   Updated: 2021/11/19 14:10:40 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bis.h"

t_env	*cpy_env_list(t_env *env)
{
	t_env   *cpy;

	cpy = NULL;
	while (env)
	{
		envadd_back(&cpy, env->name, env->value);
		env = env->next;
	}
	return (cpy);
}

t_env	*get_lowest_env_ascii(t_env *env, t_env *tmp, int size)
{
	int		valid;
	t_env	*elet;

	elet = env;
	while (elet)
	{
		tmp = env;
		valid = 1;
		while (tmp)
		{
			//a voir la precision de la comparaision
			if (my_strncmp(elet->name, tmp->name) != 1)
				valid++;
			tmp = tmp->next;
		}
		if (valid == size)
			return (elet);
		elet = elet->next;
	}
	elet = envlast(env);
	return (elet);
}