/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:39:37 by aderose           #+#    #+#             */
/*   Updated: 2021/12/26 11:39:40 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit(t_token *tk)
{
	int	j;

	j = 0;
	if (tk->len > 2)
	{
		ft_putendl_fd("Error: exit to much arguments.", 1);
		return (0);
	}
	if (tk->len == 1)
		return (1);
	while (tk->arg && tk->arg[1] && tk->arg[1][j])
	{
		if (!ft_isdigit(tk->arg[1][j]))
		{
			ft_putendl_fd("Error: exit numeric argument required.", 1);
			return (0);
		}
		j++;
	}
	g_exit_status = ft_atoi(tk->arg[1]);
	return (1);
}

void	del_heredoc(void)
{
	int		fd;

	fd = open("/tmp/1", O_RDONLY);
	if (fd != -1)
	{
		unlink("/tmp/1");
		close(fd);
	}
}

void	ft_exit(t_msh *msh)
{
	t_token	*tk;

	if (msh->node)
	{
		tk = (t_token *)msh->node->content;
		if (!check_exit(tk))
			return ;
	}
	unset_stdio(msh);
	free_myenv(msh->myenv);
	del_heredoc();
	ft_lstclear(&msh->node, &del_token);
	if (msh->pid)
	{
		free(msh->pid);
		msh->pid = NULL;
	}
	set_stdio(msh);
	ft_putendl_fd("exit", 1);
	unset_stdio(msh);
	exit(EXIT_SUCCESS);
}

void	ft_error_msh(t_msh *msh, char *str)
{
	unset_stdio(msh);
	free_myenv(msh->myenv);
	del_heredoc();
	if (msh->node)
	{
		while (msh->node->prev)
			msh->node = msh->node->prev;
		ft_lstclear(&msh->node, &del_token);
	}
	if (msh->pid)
	{
		free(msh->pid);
		msh->pid = NULL;
	}
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	ft_error(t_list **list, char *str)
{
	del_heredoc();
	if (list && *list)
	{
		while ((*list)->prev)
			(*list) = (*list)->prev;
		ft_lstclear(list, &del_token);
	}
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}
