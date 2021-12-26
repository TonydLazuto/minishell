/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:15:43 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/19 12:10:04 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/**
 * @brief Get the built in list object
 * echo tous les args
 * 
 * @return char** 
 */

char	**get_built_in_list(void)
{
	static char *array[] =
	{
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL
	};
	return (array);
}

// TODO: declare en static un tableau de stuct et/ou de string et le return via une fonction
int	is_built_in(char *str)
{
	char	**array = get_built_in_list();
	while (*array)
	{
		if (!strcmp(str, *array))
			return (1);
		array++;
	}
	return (0);
}

void	del_token(void *token)
{
	int	i;

	i = 0;
	if (((t_token *)token)->value)
	{
		free(((t_token *)token)->value);
		((t_token *)token)->value = 0;
	}
	if (((t_token *)token)->arg)
	{
		while (((t_token *)token)->arg[i])
			free(((t_token *)token)->arg[i++]);
		free(((t_token *)token)->arg);
	}
	free((t_token *)token);
	token = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*node;
	t_msh	msh;
	// t_list	*tmp;
	char	*line;
	
	node = NULL;
	(void)argc;
	(void)argv;
	msh.myenv = env_cpy(envp);
	set_global(&msh);
	while (1)
	{
		signal(SIGINT, parent_signal);
		signal(SIGQUIT, parent_signal);
		line = readline("minishell-v1$ ");
		// printf("line:%s\n", line);
		if (line && *line)
			add_history(line);
		//else
		//{
		//	rl_clear_history();
		//	break ;
		//}/
		if (!line)
			ft_exit(&msh);
		tokenization(line, &node);
		// tmp = node;
		if (parser(&node, msh.myenv, &msh))
		{
			msh.node = node;
			run_exec(&msh);
		}
		else
			g_exit_status = 127;
		ft_lstclear(&node, &del_token);
		node = NULL;
		free(line);
	}
	return (g_exit_status);
}
