/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 12:13:58 by aderose           #+#    #+#             */
/*   Updated: 2021/12/15 14:09:42 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * translate_home(t_node *node)
 * 		traduit le ~ avec le path de la var
 * 		d'environnement HOME lors du "cd"
 * maj_pwd(t_node *node)
 * 		met a jour les var d'environnements
 * 		PWD et OLDPWD apres un "cd"
 */

void	ft_pwd(t_list *node)
{
	char	*buf;

	buf = NULL;
	if (((t_token *)node->content)->len != 1)
	{
		ft_putstr_fd("Error: pwd too many arguments.\n", 1);
		return ;
	}
	buf = getcwd(buf, 0);
	if (buf)
	{
		ft_putendl_fd(buf, 1);
		ft_free(&buf);
	}
	else
		ft_putendl_fd("This folder's been deleted", 1);
}

void	check_home_env(t_msh *msh)
{
	int		line;
	char	*home_path;

	g_exit_status = 0;
	home_path = NULL;
	line = get_env_line(msh->myenv, "HOME");
	if (line == -1)
		ft_putendl_fd("Error: HOME doesn't exist.", 1);
	else
	{
		home_path = ft_strchr(msh->myenv[line], '=');
		if (home_path && *home_path != '\0' && *home_path++ != '\0')
		{
			if (chdir(home_path) == -1)
				ft_putendl_fd("Error: folder doesn't exist.", 1);
		}
		else
			ft_putendl_fd("Error: HOME has no value.", 1);
		g_exit_status = 1;
	}
}

void	maj_pwd(t_msh *msh)
{
	int		pwd_line;
	int		oldpwd_line;
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (!buf)
		ft_error_msh(msh, "Malloc oldpwd");
	pwd_line = get_env_line(msh->myenv, "PWD");
	oldpwd_line = get_env_line(msh->myenv, "OLDPWD");
	if (pwd_line >= 0 && oldpwd_line >= 0
		&& ft_strchr(msh->myenv[pwd_line], '='))
	{	
		msh->myenv[oldpwd_line] = join_env_value(msh->myenv[oldpwd_line],
				"OLDPWD", ft_strchr(msh->myenv[pwd_line], '='));
		if (!msh->myenv[oldpwd_line])
			ft_error_msh(msh, "Malloc PWD");
	}
	if (pwd_line >= 0)
		msh->myenv[pwd_line] = join_env_value(msh->myenv[pwd_line],
				"PWD=", buf);
	if (pwd_line >= 0)
		if (!msh->myenv[pwd_line])
			ft_error_msh(msh, "Malloc PWD");
	ft_free(&buf);
}

void	ft_cd(t_msh *msh)
{
	t_token	*tk;

	tk = (t_token *)msh->node->content;
	g_exit_status = 1;
	if (tk->len > 2)
	{
		ft_putstr_fd("Error: too many arguments.\n", 1);
		return ;
	}
	if (!tk->arg[1])
	{
		check_home_env(msh);
		return ;
	}
	if (chdir(tk->arg[1]) == -1)
	{
		ft_putstr_fd("Error: folder doesn't exists.\n", 1);
		return ;
	}
	maj_pwd(msh);
	g_exit_status = 0;
}
