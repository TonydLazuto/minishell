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
	// t_astnode	*node;
	t_env		*myenv;
//	char	*line_read;

	(void)ac;
	(void)av;
	// node = NULL;
	myenv = get_linked_list(env);
	while (myenv)
	{
		printf("%s\n%s\n", myenv->name, myenv->value);
		myenv = myenv->next;
	}
/*
	if (!myenv)
		return (-1);
	char **arg = (char **)malloc(sizeof(char *) * 3);
	if (!arg)
		return (0);
	arg[0] = ft_strdup("export");
	arg[1] = ft_strdup("truc=5");
	arg[2] = NULL;
	nodeadd_right(&node, arg, TK_WORD, myenv);

	nodeadd_right(&node, NULL, TK_HERE_DOC);

	char **arg3 = (char **)malloc(sizeof(char *) * 2);
	if (!arg3)
		return (0);
	arg3[0] = ft_strdup("point");
	arg3[1] = NULL;
	nodeadd_right(&node, arg3, TK_WORD, myenv);
*/
/*
	nodeadd_right(&node, NULL, TK_PIPE);

	char **arg4 = (char **)malloc(sizeof(char * ) * 3);
	if (!arg4)
		return (0);
	arg4[0] = ft_strdup("/bin/cat");
	arg4[1] = ft_strdup("-e");
	arg4[2] = NULL;
	nodeadd_right(&node, arg4, TK_WORD);

	nodeadd_right(&node, NULL, TK_OUT_REDIR);

	char **arg5 = (char **)malloc(sizeof(char * ) * 3);
	if (!arg5)
		return (0);
	arg5[0] = ft_strdup("file");
	arg5[1] = NULL;
	nodeadd_right(&node, arg5, TK_WORD);
*/
	// while (node)
	// {
	// 	if (node->type == TK_WORD)
	// 		exec_cmd(node, env);
	// 	node = node->right;
	// }
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
