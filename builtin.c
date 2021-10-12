/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:55:56 by aderose           #+#    #+#             */
/*   Updated: 2021/10/11 14:48:49 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(t_node *node)
{
	int	i;
	int	ret;

	i = 0;
	while (node->cmd.arg[i])
		i++;
	if (i != 2 || !node->cmd.arg[1])
		ft_exit(node, "error: cd bad arguments", 0);
	ret = chdir(node->cmd.arg[1]);
	if (ret == -1)
		ft_exit(node, "error: chdir", 0);
}
