/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:11:54 by aderose           #+#    #+#             */
/*   Updated: 2021/12/08 13:53:51 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * INFO
 * env name (or key)
 * A word consisting solely of letters, numbers, and underscores,
 * and beginning with a letter or underscore.
 * 
 * Le dollar $ apres le mot export
 * devrait etre une error mais passe
 */

int	check_valid_name(char *arg)
{
	int	j;

	j = 0;
	if (!ft_isalpha(arg[j]) && arg[j] != '_')
		return (0);
	j++;
	while (arg[j] && arg[j] != '+' && arg[j] != '=')
	{
		if (!ft_isalnum(arg[j]) && arg[j] != '_')
			return (0);
		j++;
	}
	return (1);
}

char	*get_name(t_msh *msh, char *arg)
{
	char	*name;
	char	*equal;
	char	*sep;

	equal = ft_strchr(arg, '=');
	sep = ft_strnstr(arg, "+=", ft_strlen(arg));
	name = NULL;
	if (sep)
		name = ft_substr(arg, 0, sep - arg);
	else if (equal)
		name = ft_substr(arg, 0, equal - arg);
	else
		name = ft_strdup(arg);
	if (!name)
		ft_error_msh(msh, "malloc name env.");
	return (name);
}

void	ft_export2(t_msh *msh, char *arg)
{
	char	*name;
	int		line;

	name = get_name(msh, arg);
	line = get_env_line(msh->myenv, name);
	if (line == -1)
		export_new(msh, arg, name);
	else
		modify_export(msh, line, arg);
	ft_free(&name);
}

void	ft_export(t_msh *msh)
{
	t_token	*tk;
	int		i;

	i = 1;
	tk = (t_token *)msh->node->content;
	g_exit_status = 0;
	if (tk->len == 1)
	{
		print_export(msh);
		return ;
	}
	while (tk->arg[i])
	{
		if (!check_valid_name(tk->arg[i]))
		{
			ft_putendl_fd("invalid export.", STDOUT_FILENO);
			return ;
		}
		ft_export2(msh, tk->arg[i]);
		i++;
	}
}
