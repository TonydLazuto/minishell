/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:15:43 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/29 18:15:59 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int		g_exit_status;

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

char	*get_line_rdl(t_msh *msh)
{
	char	*line;

	signal(SIGINT, parent_signal);
	signal(SIGQUIT, parent_signal);
	line = readline("minishell$ ");
	if (line && *line)
		add_history(line);
	if (!line)
	{
		free(line);
		ft_exit(msh);
	}
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*node;
	t_msh	msh;
	char	*line;

	node = NULL;
	(void)argc;
	(void)argv;
	msh.myenv = env_cpy(envp);
	set_global(&msh);
	while (1)
	{
		line = get_line_rdl(&msh);
		tokenization(line, &node);
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
