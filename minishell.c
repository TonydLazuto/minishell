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
export A+=qwe
export A+=rty
--> A=qwerty

export MAVAR="ls -a"
$MAVAR
--> command not found ls -a

cat << ""

echo $truc
--> si truc n'est pas dans env \n

MANDATORY PATH DIFF !!!

*/

/**
 * int rl_on_new_line ()
 * Tell the update routines that we have moved onto a new (empty) line,
 * usually after ouputting a newline.
 * 
 * int rl_redisplay ()
 * Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
 * 
 */
int	main(int ac, char *av[], char **envp)
{
	t_astnode	*node;
	t_env		*env;
	// char		*line_read;

	(void)ac;
	(void)av;
	node = NULL;
	env = get_linked_list(envp);
	if (!env)
		return (-1);

	char **arg = (char **)malloc(sizeof(char *) * 3);
	if (!arg)
		return (0);
	arg[0] = ft_strdup("export");
	arg[1] = ft_strdup("MANEWVAR");
	arg[2] = NULL;
	nodeadd_right(&node, arg, NODE_WORD, env);

	// nodeadd_right(&node, NULL, NODE_HERE_DOC, env);
	// char **arg2 = (char **)malloc(sizeof(char * ) * 2);
	// if (!arg2)
	// 	return (0);
	// arg2[0] = ft_strdup("env");
	// arg2[1] = NULL;
	// nodeadd_right(&node, arg2, NODE_WORD, env);


	char **arg3 = (char **)malloc(sizeof(char *) * 3);
	if (!arg3)
		return (0);
	arg3[0] = ft_strdup("export");
	arg3[1] = NULL;
	arg3[2] = NULL;
	nodeadd_right(&node, arg3, NODE_WORD, env);

	// nodeadd_right(&node, NULL, NODE_PIPE, env);

	// char **arg4 = (char **)malloc(sizeof(char * ) * 3);
	// if (!arg4)
	// 	return (0);
	// arg4[0] = ft_strdup("/usr/bin/grep");
	// arg4[1] = ft_strdup("MANEWVAR");
	// arg4[2] = NULL;
	// nodeadd_right(&node, ./arg4, NODE_WORD, env);

	// nodeadd_right(&node, NULL, NODE_OUT_REDIR);

	// char **arg5 = (char **)malloc(sizeof(char * ) * 3);
	// if (!arg5)
	// 	return (0);
	// arg5[0] = ft_strdup("unset");
	// arg5[1] = ft_strdup("MANEWVAR");
	// arg5[2] = NULL;
	// nodeadd_right(&node, arg5, NODE_WORD, env);

	// char **arg6 = (char **)malloc(sizeof(char *) * 3);
	// if (!arg6)
	// 	return (0);
	// arg6[0] = ft_strdup("env");
	// arg6[1] = NULL;
	// arg6[2] = NULL;
	// nodeadd_right(&node, arg6, NODE_WORD, env);

	t_astnode *first;
	first = node;
	while (node)
	{
		if (node->type == NODE_WORD)
			exec_cmd(node, envp);
		node = node->right;
	}
	clear_env(&env);
	clearnodes(&first);
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
