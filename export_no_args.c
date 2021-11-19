/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 13:29:29 by aderose           #+#    #+#             */
/*   Updated: 2021/11/19 13:29:31 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * La ligne de l'env dont le name est "_"
 * n'est pas dans l'export selon bash.
 */

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
	if (get_env_size(env) == 1)
		return (env);
	while (elet)
	{
		tmp = env;
		valid = 0;
		while (tmp)
		{
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
	free(del_elet);
	del_elet = NULL;
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

void	print_env_line(t_env *env)
{
	if (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->name, 1);
		if (env->value)
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(env->value, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
	}
}

void	export_no_args(t_astnode *node)
{
	t_env	*lowest;
	t_env	*cpy;

	cpy = cpy_env_list(node->env);
	while (cpy)
	{
		lowest = get_lowest_env_ascii(cpy, NULL, get_env_size(cpy));
		if (my_strncmp(lowest->name, "_") != 0)
			print_env_line(lowest);
		cpy = pop_env(cpy, lowest->name);
	}
}
