/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:02:06 by aderose           #+#    #+#             */
/*   Updated: 2021/10/11 14:50:48 by aderose          ###   ########.fr       */
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
//	t_node		*node;
	char	*line;
	(void)ac;
	(void)av;
	(void)env;

	line = NULL;

		line = readline("Here: ");
	free(line);
	return (0);
}
