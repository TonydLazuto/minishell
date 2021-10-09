/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:02:06 by aderose           #+#    #+#             */
/*   Updated: 2021/09/16 10:02:08 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
echo "ls"
--> affiche ls

export qwe="ls"
$qwe
--> execute ls

export qwe="ls -a"
$qwe
--> command not found ls -a
*/

int	main(int ac, char *av[])
{
	t_node	*node;
	t_node	*node2;
	t_node	*node3;
	t_node	*node4;
	t_node	*node5;
	t_node	*node6;
	t_node	*node7;
	t_node	*node8;

	node = new_node(BREAK);
	if (!node)
		ft_exit(node);
	return (0);
}
