/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 12:13:58 by aderose           #+#    #+#             */
/*   Updated: 2021/11/20 12:14:01 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_node *node)
{
	t_env	*elet;

	elet = node->cmd.env;
	if (!node->cmd.arg[1])
		return ;
	elet = get_env_by_name(node->cmd.env, node->cmd.arg[1]);
	if (elet)
		node->cmd.env = pop_env(node->cmd.env, elet->name);
}

void	ft_exit(t_node *node)
{
	while (node->back)
		node = node->back;
	clearnodes(&node);
	exit(EXIT_SUCCESS);
}
