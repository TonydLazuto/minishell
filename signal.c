/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:31:09 by aderose           #+#    #+#             */
/*   Updated: 2021/12/19 11:42:51 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_signal(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 2);
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		// rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	child_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core dumped)\n", 2);
		g_exit_status = 131;
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_exit_status = 130;
	}
}
