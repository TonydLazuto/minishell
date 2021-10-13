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
	t_cmd	*cmd;
//	char	*line_read;

	(void)ac;
	(void)av;
	cmd = NULL;

	char **arg = (char **)malloc(sizeof(char * ) * 3);
	if (!arg)
		return (0);
	arg[0] = ft_strdup("/usr/bin/ls");
	arg[1] = ft_strdup("-l");
	arg[2] = NULL;
	cmdadd_back(&cmd, arg, PIPE);

	char **arg2 = (char **)malloc(sizeof(char * ) * 3);
	if (!arg2)
		return (0);
	arg2[0] = ft_strdup("/usr/bin/grep");
	arg2[1] = ft_strdup("min");
	arg2[2] = NULL;
	cmdadd_back(&cmd, arg2, END);


	while (cmd)
	{
		pipes(cmd, env);
		cmd = cmd->next;
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
