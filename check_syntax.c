/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:21:35 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/15 14:11:11 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_redir(t_list *node)
{
	t_token	*tk;
	t_token	*tk_next;

	while (node)
	{
		tk = (t_token *)node->content;
		tk_next = get_next_token(node);
		if (is_redirection(tk->type))
			if ((tk_next && tk_next->type != TK_WORD) || !tk_next)
				return (0);
		node = node->next;
	}
	return (1);
}

int	check_syntax_pipe(t_list *node)
{
	t_token	*tk;
	t_token	*tk_next;

	if (node)
	{
		tk = (t_token *)node->content;
		tk_next = get_next_token(node);
		if (tk->type == TK_PIPE)
			return (0);
	}
	while (node)
	{
		tk = (t_token *)node->content;
		tk_next = get_next_token(node);
		if (tk->type == TK_PIPE)
			if ((tk_next && tk_next->type == TK_PIPE) || !tk_next)
				return (0);
		node = node->next;
	}
	return (1);
}
