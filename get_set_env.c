/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:27:54 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/22 19:18:27 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	set_env_var(char *str, char **env, t_msh *msh)
{
	t_env_var	d_env_var;
	char		*tmp;
	int			i;
	char		*venv;

	i = 1;
	while (ft_isalnum(*(str + i)))
		i++;
	tmp = ft_strndup(str + 1, i - 1);
	venv = get_env_value(tmp, env, msh);
	if (venv && *venv)
		d_env_var.value = ft_strdup(venv);
	else
		d_env_var.value = ft_strdup("");
	free(tmp);
	if (ft_isdigit(*(str + 1)))
		d_env_var.rest = ft_strdup(str + 2);
	else
		d_env_var.rest = ft_strdup(str + i);
	if (i == 1)
	{
		free(d_env_var.value);
		d_env_var.value = ft_strdup("$");
	}
	return (d_env_var);
}

void	replace_env(char **str, char **env, t_msh *msh)
{
	char		*test;
	char		*tmp;
	t_env_var	d_env_var;

	test = ft_strchr(*str, '$');
	while (test)
	{
		d_env_var = set_env_var(test, env, msh);
		tmp = *str;
		*str = fusion(ft_strndup(*str, test - *str), d_env_var);
		test = ft_strchr(*str + (test - tmp) + ft_strlen(d_env_var.value), '$');
		free(tmp);
		free(d_env_var.value);
		free(d_env_var.rest);
	}
}

void	get_set_env(t_list *tokens, char **env, t_msh *msh)
{
	t_token	*tk;
	char	*tmp;

	while (tokens)
	{
		tk = (t_token *)tokens->content;
		if (tk->type == TK_WORD)
		{
			if (*(tk->value) != '\'' && ft_strchr(tk->value, '$'))
				replace_env(&tk->value, env, msh);
			if (*(tk->value) == '\'' || *(tk->value) == '\"')
			{
				tmp = tk->value;
				tk->value = ft_substr(tk->value, 1, ft_strlen(tk->value) - 2);
				free(tmp);
			}
			else if (ft_strchr(tk->value, ' '))
				cut_space(tokens);
		}
		tokens = tokens->next;
	}
}
