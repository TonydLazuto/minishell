/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:57:19 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/22 18:57:12 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(t_list *node)
{
	t_token	*tk;

	while (node)
	{
		tk = (t_token *)node->content;
		if (tk->type == TK_WORD)
		{
			if (*tk->value == '\'' || *tk->value == '\"')
			{
				if (tk->value[0] != tk->value[ft_strlen(tk->value) - 1])
				{
					printf("unclosed simple quote or double quote\n");
					return (0);
				}
			}
		}
		node = node->next;
	}
	return (1);
}

void	erase_quotes(t_list *node)
{
	t_token	*tk;
	char	*tmp;

	while (node)
	{
		tk = (t_token *)node->content;
		if (tk->type == TK_WORD)
		{
			if (*(tk->value) == '\'' || *(tk->value) == '\"')
			{
				tmp = tk->value;
				tk->value = ft_substr(tk->value, 1, ft_strlen(tk->value) - 2);
				free(tmp);
			}
		}
		node = node->next;
	}
}

void	simplification(t_list *node)
{
	t_list	*lst;
	t_token	*tk;

	lst = node;
	while (lst)
	{
		tk = (t_token *)lst->content;
		if (is_redirection(tk->type))
			simplification_redir(lst);
		else if (tk->type == TK_WORD)
		{
			tk->arg = set_arg(lst);
			tk->len = get_nb_args(lst);
			tk->type = TK_CMD;
			lst->next = ft_lstdeln(&lst->next, del_token, (tk->len - 1));
			if (lst->next)
				lst->next->prev = lst;
		}
		lst = lst->next;
	}
}

int	parser(t_list **node, char **env, t_msh *msh)
{
	if (check_quotes(*node))
	{
		get_set_env(*node, env, msh);
		parse_word(*node);
		erase_space(*node);
		if (check_syntax_redir(*node))
		{
			simplification(*node);
			if (!check_syntax_pipe(*node))
			{
				printf("Syntax error.\n");
				return (0);
			}
			get_heredoc(*node);
		}
		else
		{
			printf("Syntax error.\n");
			return (0);
		}
	}
	else
		return (0);
	return (1);
}
