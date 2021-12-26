/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:45:26 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/13 14:49:19 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_env_intero(t_token *tk)
{
	int		i;
	char	*test;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (tk->arg)
	{
		while (tk->arg[i])
		{
			test = ft_strchr(tk->arg[i], '$');
			if (test && *(test + 1) == '?')
			{
				*test = (g_exit_status + 48);
				tmp = tk->arg[i];
				tmp2 = ft_strndup(tk->arg[i], (test - tk->arg[i] + 1));
				tk->arg[i] = ft_strjoin(tmp2, (test + 2));
				free(tmp);
				free(tmp2);
			}
			i++;
		}
	}
}

void	erase_space(t_list *node)
{
	t_token	*next_tk;
	t_list	*tmp;

	while (node)
	{
		next_tk = get_next_token(node);
		if (next_tk && next_tk->type == TK_WHITE_SPACE)
		{
			tmp = node->next;
			if (node->next->next)
				node->next->next->prev = node;
			node->next = node->next->next;
			ft_lstdelone(tmp, &del_token);
		}
		node = node->next;
	}
}

int	get_nb_args(t_list *node)
{
	t_token	*tk;
	int		len;

	len = 0;
	tk = (t_token *)node->content;
	while (node && tk->type == TK_WORD)
	{
		len++;
		node = node->next;
		if (node)
			tk = (t_token *)node->content;
	}
	return (len);
}

char	**set_arg(t_list *node)
{
	t_token	*tk;
	char	**result;
	int		len;
	int		i;

	i = 0;
	len = get_nb_args(node);
	result = malloc(sizeof(*result) * (len + 1));
	if (!result)
		return (NULL);
	tk = (t_token *)node->content;
	while (node && tk->type == TK_WORD)
	{
		result[i++] = ft_strdup(tk->value);
		node = node->next;
		if (node)
			tk = (t_token *)node->content;
	}
	result[i] = NULL;
	return (result);
}

void	parse_word(t_list *node)
{
	t_token	*tk;
	t_token	*next_tk;
	char	*tmp;
	t_list	*list_tmp;

	while (node)
	{
		tk = (t_token *)node->content;
		if (tk->type == TK_WORD)
		{
			next_tk = get_next_token(node);
			while (next_tk && next_tk->type == TK_WORD)
			{
				tmp = tk->value;
				tk->value = ft_strjoin(tk->value, next_tk->value);
				free(tmp);
				list_tmp = node->next;
				node->next = node->next->next;
				ft_lstdelone(list_tmp, &del_token);
				next_tk = get_next_token(node);
			}
		}
		node = node->next;
	}
}
