/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:08:14 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/14 16:50:07 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simplification_redir(t_list *node)
{
	t_token	*tk;
	t_token	*tk_next;
	char	*tmp;

	tk = (t_token *)node->content;
	tk_next = get_next_token(node);
	if (tk_next)
	{
		if (tk_next->type == TK_WORD)
		{
			tmp = tk->value;
			tk->value = ft_strdup(tk_next->value);
			free(tmp);
			cut_and_join(node);
		}
		else
			printf("Syntax error.\n");
	}
	else
		printf("Syntax error.\n");
}
