/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:31:53 by aderose           #+#    #+#             */
/*   Updated: 2021/12/10 13:31:54 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_stdio(t_msh *msh)
{
	msh->save_stdin = dup(STDIN_FILENO);
	msh->save_stdout = dup(STDOUT_FILENO);
}

void	unset_stdio(t_msh *msh)
{
	dup2(msh->save_stdin, STDIN_FILENO);
	close(msh->save_stdin);
	dup2(msh->save_stdout, STDOUT_FILENO);
	close(msh->save_stdout);
}

void	set_global(t_msh *msh)
{
	g_exit_status = 0;
	msh->pid = NULL;
}
