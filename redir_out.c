/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:47:49 by aderose           #+#    #+#             */
/*   Updated: 2021/10/11 17:31:38 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * 	if cmd->arg == NULL
 * 		child_stdin() //redirige sur STDIN
 */
/*
void	append_args_to_file(t_cmd *cmd)
{
	int	fd;
	int	i;

	i = 1;
	fd = open(cmd->next->arg[0], O_APPEND);
	if (fd == -1)
		ft_exit(node, "error : fatal");
	while (cmd->next->arg[i])
	{
		write(fd, (void *)cmd->next->arg[i], ft_strlen(cmd->next->arg[i]));
		if (cmd->next->arg[i + 1])
			write(fd, " ", 1);
		i++;
	}
}

void	check_exceptions(t_cmd *cmd)
{
	if (!cmd->arg)
	{
		if (cmd->next && cmd->next->type == PIPE)
				;
	}
}
*/
void	child_redi(t_cmd *cmd, char **env)
{
	int			file;
/*	int		ret;

	ret = access(cmd->next->arg[0], R_OK | W_OK);
	if (ret == -1)
		ft_exit(cmd, "error : access()");
*/
	file = open(cmd->next->arg[0], O_RDWR | O_CREAT);
	if (file == -1)
		ft_exit(cmd, "error : open()");
	if (cmd->arg != NULL)
	{
		if (dup2(file, 1) < 0)
			ft_exit(cmd, "error : fatal");	
	}
	close(file);
	if ((cmd->next && cmd->next->type != REDIR_OUT)
			|| !cmd->next)
	{
		if (execve(cmd->arg[0], cmd->arg, env) == -1)
			ft_exit(cmd, "error: cannot execve");
	}
}

t_cmd	*redir_out(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		status;

	if (!cmd->next)
 		ft_exit(cmd, "syntax error near unexpected token newline");
	pid = fork();
	if (pid < 0)
		ft_exit(cmd, "error : fatal");
	if (pid == 0)
		child_redi(cmd, env);
	else
		waitpid(pid, &status, 0);
	return (cmd);
}
