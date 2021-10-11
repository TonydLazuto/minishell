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

int	main(int ac, char *av[], char **env)
{
	t_node	*node;
	t_node	*node2;
	t_node	*node3;

	(void)ac;
	(void)av;

	const char *arg1[] = {
		"/usr/bin/ls",
		"-l",
		NULL
	};
	const char *arg2[] = {
		"/usr/bin/grep",
		"no",
		NULL
	};
	const char *arg3[] = {
		"/usr/bin/cat",
		"-e",
		NULL
	};

	node = new_node(BREAK);
	if (!node)
		ft_exit(node, "err create node");
	node2 = push_right(node, CMD, arg1, PIPE);
	node3 = push_right(node2, CMD, arg2, PIPE);
	push_right(node3, CMD, arg3, END);

	while (node)
	{
		pipes(node, env);
		node = node->right;
	}
	//printnodes(node);
	clear_node(node);
	return (0);
}
