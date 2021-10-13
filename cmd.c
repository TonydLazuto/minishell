/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:34:50 by aderose           #+#    #+#             */
/*   Updated: 2021/10/12 16:35:02 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(char **arg, int type)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->arg = arg;
	cmd->pipefd[0] = 0;
	cmd->pipefd[1] = 0;
	cmd->type = type;
	cmd->next = NULL;
	cmd->back = NULL;
	return (cmd);
}
t_cmd	*cmdlast(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void		clearcmds(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = NULL;
	if (*cmd)
	{
		while (*cmd)
		{
			tmp = (*cmd)->next;
			if ((*cmd)->arg)
			{
				i = 0;
				while ((*cmd)->arg[i])
				{
					free((*cmd)->arg[i]);
					i++;
				}
				free((*cmd)->arg);
			}
			free(*cmd);
			*cmd = NULL;
			*cmd = tmp;
		}
	}
}

void	cmdadd_back(t_cmd **acmd, char *arg[], int type)
{
	t_cmd	*cmd;
	t_cmd	*new;

	new = new_cmd(arg, type);
	if (!new)
		return ;
	if (!*acmd)
	{
		*acmd = new;
		return ;
	}
	cmd = cmdlast(*acmd);
	cmd->next = new;
	new->back = cmd;
}
