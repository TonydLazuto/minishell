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

void	print_node(t_node *node)
{
	if (!node)
		return ;
	if (node->left)
		print_node(node->left);
	if (node->right)
		print_node(node->right);
	printf("node : %d\n", node->info.type);
}

int		main(int ac, char *av[])
{
	t_node	*node;
	t_node	*node2;
	t_node	*node3;
	t_node	*node4;
	t_node	*node5;
	t_node	*node6;
	t_node	*node7;
	t_node	*node8;
	t_info	info;

	info.node_info = NULL;
	info.debug = NULL;
	node = NULL;
	if (ac >= 2 || av[1])
		return (0);

	node = new_node(info);
	node->info.type = 1;
	if (!node)
	{
		clear_node(node2);
		return (0);
	}
	node2 = new_node(info);
	node2->info.type = 2;
	if (!node2)
	{
		clear_node(node);
		return (0);
	}
	node3 = push_parent(node, node2, info);
	node3->info.type = 3;
	node4 = push_parent(node3, NULL, info);
	node4->info.type = 4;
	node5 = push_parent(node4, NULL, info);
	node5->info.type = 5;
	node6 = push_right(node5, info);
	node6->info.type = 6;
	node7 = push_right(node6, info);
	node7->info.type = 7;
	node8 = push_right(node6, info);
	node8->info.type = 8;
	print_node(node6);
	clear_node(node5);
	//print_node(node5);
	return (0);
}