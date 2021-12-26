/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:16:03 by aderose           #+#    #+#             */
/*   Updated: 2021/12/08 12:11:06 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_value(t_msh *msh, int i, int j)
{
	if (msh->myenv[i][j])
	{
		ft_putchar_fd('=', 1);
		ft_putchar_fd('"', 1);
		j++;
		while (msh->myenv[i][j])
		{
			ft_putchar_fd(msh->myenv[i][j], 1);
			j++;
		}
		ft_putchar_fd('"', 1);
	}
}

void	print_export(t_msh *msh)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (msh->myenv[i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (msh->myenv[i][j] && msh->myenv[i][j] != '=')
		{
			ft_putchar_fd(msh->myenv[i][j], 1);
			j++;
		}
		print_export_value(msh, i, j);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	export_new(t_msh *msh, char *arg, char *name)
{
	char	*s;
	char	*val;

	val = ft_strchr(arg, '=');
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		s = ft_strjoin(name, val);
	else
		s = ft_strdup(arg);
	msh->myenv = env_add(msh->myenv, s);
	ft_free(&s);
}

void	modify_export(t_msh *msh, int line, char *arg)
{
	char	*val;
	char	*tmp;

	tmp = NULL;
	val = ft_strchr(arg, '=');
	if (!val || *val == '\0' || *val++ == '\0')
		return ;
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
	{
		tmp = ft_strdup(msh->myenv[line]);
		msh->myenv[line] = join_env_value(msh->myenv[line], tmp, val);
		ft_free(&tmp);
	}
	else
		msh->myenv[line] = replace_env_line(msh->myenv[line], arg);
}
