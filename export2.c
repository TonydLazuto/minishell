/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:16:03 by aderose           #+#    #+#             */
/*   Updated: 2021/11/26 14:16:07 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_append(t_node *node, char **name, char **val)
{
	size_t			len;
	unsigned int	start;

	len = 1;
	while (node->cmd.arg[1][len] != '+')
		len++;
	*name = ft_substr(node->cmd.arg[1], 0, len);
	if (!*name)
		ft_error(node, "export: malloc");
	len++;
	start = len + 1;
	if (!node->cmd.arg[1][len])
		return ;
	while (node->cmd.arg[1][len])
		len++;
	*val = ft_substr(node->cmd.arg[1], start, len);
	if (!*val)
		ft_error(node, "export: malloc");
}

void	export_append(t_node *node)
{
	t_env	*elet;
	char	*name;
	char	*val;

	name = NULL;
	val = NULL;
	split_append(node, &name, &val);
	elet = get_env_by_name(node->cmd.env, name);
	if (elet)
	{
		elet->value = strjoinfree(elet->value, val);
		if (!elet->value)
			ft_error(node, "export: malloc export_append()");
	}
	else
		envadd_back(&node->cmd.env, name, val);
}

void	split_normal(t_node *node, char **name, char **val)
{
	size_t			len;
	unsigned int	start;

	len = 1;
	while (node->cmd.arg[1][len] != '=')
		len++;
	start = len + 1;
	*name = ft_substr(node->cmd.arg[1], 0, len);
	if (!*name)
		ft_error(node, "export: malloc");
	if (!node->cmd.arg[1][len])
		return ;
	while (node->cmd.arg[1][len])
		len++;
	*val = ft_substr(node->cmd.arg[1], start, len);
	if (!*val)
		ft_error(node, "export: malloc");
}

void	export_normal(t_node *node)
{
	t_env	*elet;
	char	*name;
	char	*val;

	name = NULL;
	val = NULL;
	split_normal(node, &name, &val);
	elet = get_env_by_name(node->cmd.env, name);
	if (elet)
	{
		free(elet->value);
		elet->value = ft_strdup(val);
	}
	else
		envadd_back(&node->cmd.env, name, val);
}
