/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:44:35 by aderose           #+#    #+#             */
/*   Updated: 2021/09/16 10:44:41 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		my_strcmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (str1[i] != str2[i])
	{
		if (str1[i] - str2[i] > 0)
			return (1);
		else
			return (-1);
	}
	return (0);
}

t_node	*find_arg(t_node *node, char *arg)
{
	if (!node)
		return (NULL);
	printf("node cur : %d\n", node->type);
	//if (my_strcmp(node->arg, arg) == 0)
	if (node->type == 6)
	{
		printf("yo\n");
		return (node);
	}
	find_arg(node->left, arg);
	find_arg(node->right, arg);
	return (node);
}