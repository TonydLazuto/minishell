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

#include "minishell_bis.h"

t_env   *pop_env(t_env *env, t_env *elet)
{
	t_env	*tmp;
	t_env	*before;
	t_env	*after;

	tmp = env;
	while (tmp
			&& (ft_strlen(tmp->name) != ft_strlen(elet->name)
			&& my_strncmp(tmp->name, elet->name) != 0))
		tmp = tmp->next;
	before = tmp->back;
	after = tmp->next;
	free(tmp);
	tmp = NULL;
	if (after)
		after->back = before;
	if (before)
		before->next = after;
	while (before->back)
		before = before
	return (env);
}

void    print_env_line(t_env *env)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env->name, 1);
	ft_putchar_fd('=', 1);
	ft_putstr_fd(env->value, 1);
	ft_putchar_fd('\n', 1);
}

void    export_no_args(t_astnode *node)
{
	t_env   *lowest;
	t_env   *cpy;

	cpy = cpy_env_list(node->env);
	while (cpy)
	{
		if (get_env_size(cpy) == 1)
		{
			print_env_line(cpy);
			free(cpy);
			cpy = NULL;
			break ;
		}
		lowest = get_lowest_env_ascii(cpy, NULL, get_env_size(cpy));
		print_env_line(lowest);
		cpy = pop_env(cpy, lowest);
	}
}