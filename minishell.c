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

#include "minishell_bis.h"

/*
echo "ls"
--> affiche ls

export A+=qwe
export A+=rty
--> A=qwerty

export MAVAR="ls -a"
$MAVAR
--> command not found ls -a

cat << ""

echo $truc
--> si truc n'est pas dans env \n

*/

/**
 * int rl_on_new_line ()
 * Tell the update routines that we have moved onto a new (empty) line,
 * usually after ouputting a newline.
 * 
 * int rl_redisplay ()
 * Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
 */
int	main(int ac, char *av[], char **env)
{
	t_astnode	*node;
//	char	*line_read;

	(void)ac;
	(void)av;
	node = NULL;
/*
	char **arg = (char **)malloc(sizeof(char * ) * 3);
	if (!arg)
		return (0);
	arg[0] = ft_strdup("echo");
	arg[1] = ft_strdup("yessir");
	arg[2] = NULL;
	nodeadd_right(&node, arg, PIPE);
*/
	char **arg2 = (char **)malloc(sizeof(char * ) * 3);
	if (!arg2)
		return (0);
	arg2[0] = ft_strdup("cd");
	arg2[1] = ft_strdup("/usr/bi");
	arg2[2] = NULL;
	// arg2[1] = ft_strdup("-e");
	// arg2[2] = NULL;
	nodeadd_right(&node, arg2, END);

	char **arg3 = (char **)malloc(sizeof(char * ) * 2);
	if (!arg3)
		return (0);
	arg3[0] = ft_strdup("ls");
	arg3[1] = ft_strdup("-l");
	arg3[2] = NULL;
	nodeadd_right(&node, arg3, END);

	while (node)
	{
		exec_node(node, env);
		node = node->right;
	}
	
/*
	while (1)
	{
		line_read = readline("minishell-v1$ ");
		if (line_read && *line_read)
		{
			add_history(line_read);

		}
		else
		{
			rl_clear_history();
			break ;
		}
		free(line_read);
	}
	free(line_read);
*/
	return (0);
}
