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

cat << ""

MANDATORY PATH DIFF !!!

export MYLS="ls -la"
$MYLS : works
"$MYLS" : command not found

<< oui | << non
> oui
> non

CTRL+C = SIGINT
CTRL+\ = SIGQUIT
CTRL+D = n'est pas un signal,
c'est une touche de controle
qui envoie un end of file a ton readline

ls > out | cat file > out2
pour cette ligne j'ai le meme comportement mais
pas de messages command not found sur mon programme lol
c'est pas grave du coup?

ls << qqch | cat-e
ctrl-\ quitte un minishell
commandes pipes dans here doc + ctrl-\

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

char	**set_args(char *s1, char *s2, char *s3)
{
	char **arg;
	
	arg = (char **)malloc(sizeof(char *) * 4);
	if (!arg)
		return (NULL);
	arg[0] = NULL;
	arg[1] = NULL;
	arg[2] = NULL;
	if (s1)
		arg[0] = ft_strdup(s1);
	if (s2)
		arg[1] = ft_strdup(s2);
	if (s3)
		arg[2] = ft_strdup(s3);
	arg[3] = NULL;
	return (arg);
}
int	main(int ac, char *av[], char **envp)
{
	t_node	*node;
	t_env	*env;
	// char	*line_read;

	(void)ac;
	(void)av;
	node = NULL;
	env = get_linked_list(envp);
	if (!env)
		return (-1);

	char **arg3 = set_args("ls", NULL, NULL);
	nodeadd_back(&node, arg3, NODE_CMD, env);
	
	char **arg61 = set_args("out", NULL, NULL);
	nodeadd_back(&node, arg61, NODE_OUT_REDIR, env);

	// nodeadd_back(&node, NULL, NODE_PIPE, env);

	char **arg62 = set_args("out2", NULL, NULL);
	nodeadd_back(&node, arg62, NODE_OUT_REDIR, env);

	char **arg63 = set_args("out3", NULL, NULL);
	nodeadd_back(&node, arg63, NODE_OUT_REDIR, env);
	

	// char **arg2 = set_args("export", "TEST+=123", NULL);
	// nodeadd_back(&node, arg2, NODE_CMD, env);

	// char **arg9 = set_args("env", NULL, NULL);
	// nodeadd_back(&node, arg9, NODE_CMD, env);
	// nodeadd_back(&node, NULL, NODE_PIPE, env);
	// char **arg10 = set_args("grep" , "TEST", NULL);
	// nodeadd_back(&node, arg10, NODE_CMD, env);

	// char **arg1 = set_args("cd", "/usr/bin", NULL);
	// nodeadd_back(&node, arg1, NODE_CMD, env);

	// char **arg5 = set_args("env", NULL, NULL);
	// nodeadd_back(&node, arg5, NODE_CMD, env);
	// nodeadd_back(&node, NULL, NODE_PIPE, env);
	// char **arg11 = set_args("grep" , "PWD", NULL);
	// nodeadd_back(&node, arg11, NODE_CMD, env);

	// char **arg7 = set_args("export", NULL, NULL);
	// nodeadd_back(&node, arg7, NODE_CMD, env);

	// char **arg8 = set_args("myexport2", NULL, NULL);
	// nodeadd_back(&node, arg8, NODE_OUT_REDIR, env);

	t_node *first;
	first = node;
	while (node)
	{
		if (node->type == NODE_CMD)
			exec_cmd(node, envp);
		node = node->next;
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
