/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:55:56 by aderose           #+#    #+#             */
/*   Updated: 2021/12/15 14:09:00 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ft_unset(t_node *node)
 * 		supprime 
 * check_dash_n(t_node *node)
 * 		check echo -nnnnnnnn salut
 * 		si le "-n" ne contient bien que des "n"
 * ft_env(t_node *node)
 * 		affiche ma liste chainee d'environnement
 * 		uniquement si la value associee existe
 */

void	ft_unset(t_msh *msh, t_token *tk)
{
	int		line;
	char	**tmp_env;
	int		i;

	g_exit_status = 1;
	tmp_env = NULL;
	if (!tk->arg[1])
		return ;
	i = 1;
	while (tk->arg[i])
	{
		line = get_env_line(msh->myenv, tk->arg[i]);
		if (msh->myenv && line >= 0)
		{
			tmp_env = env_after_unset(msh->myenv, line);
			free_myenv(msh->myenv);
			msh->myenv = env_cpy(tmp_env);
			free_myenv(tmp_env);
		}
		i++;
	}
	g_exit_status = 0;
}

int	check_dash_n(t_token *tk, int *num, int newline)
{
	int	j;

	while (tk->arg[*num]
		&& (tk->arg[*num][0] == '-' && (tk->arg[*num][1] == 'n')))
	{
		j = 2;
		while (tk->arg[*num][j] && tk->arg[*num][j] == 'n')
			j++;
		if (j != (int)ft_strlen(tk->arg[*num]))
			return (newline);
		*num += 1;
		newline = 1;
	}
	return (newline);
}

void	ft_echo(t_list *node)
{
	t_token	*tk;
	int		newline;
	int		i;

	newline = 0;
	i = 1;
	tk = (t_token *)node->content;
	if (tk->len == 1)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (check_dash_n(tk, &i, newline))
		newline = 1;
	while (tk->arg[i])
	{
		ft_putstr_fd(tk->arg[i], 1);
		i++;
		if (tk->arg[i])
			ft_putstr_fd(" ", 1);
	}
	if (newline == 0)
		ft_putstr_fd("\n", 1);
}

void	ft_env(t_msh *msh)
{
	int		i;
	t_token	*tk;

	i = 0;
	tk = (t_token *)msh->node->content;
	if (tk->len != 1)
	{
		ft_putstr_fd("Error: env too many arguments.\n", 1);
		return ;
	}
	if (msh->myenv)
	{
		while (msh->myenv[i])
		{
			if (ft_strchr(msh->myenv[i], '='))
				ft_putendl_fd(msh->myenv[i], 1);
			i++;
		}
	}
}
