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
	/*
	while (node)
	{
		printf("node : %d\n", node->type);
		node = node->right;
	}
	*/
	print_node(node->left);
	print_node(node->right);
	printf("node : %d\n", node->type);
}

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

	node = NULL;
	if (ac >= 2 || av[1])
		return (0);
	node = new_node(1, NULL);
	if (!node)
	{
		clear_node(node);
		return (0);
	}
	node2 = push_right(node, 2);
	node3 = push_left(node, 3);

	node4 = push_left(node2, 4);
	node5 = push_right(node2, 5);

	node6 = push_right(node5, 6);
	node7 = push_right(node6, 7);
	node8 = push_left(node6, 8);

	print_node(node4);
	printf("------------------\n");
	rewind_tree(&node2);
	print_node(node2);
	printf("------------------\n");
	clear_node(node2);
	printf("------------------\n");
	rewind_tree(&node3);
	printf("%d\n", find_arg(node3, NULL));
	return (0);
}
