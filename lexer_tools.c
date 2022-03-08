/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:24:53 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/08 13:09:43 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *str, enum e_tk_type type)
{
	t_token	*new;

	new = malloc(sizeof(*new));
	new->value = str;
	new->type = type;
	new->arg = NULL;
	return (new);
}

int	is_in_word(enum e_state state)
{
	if (state == STATE_IN_DQUOTE || state == STATE_IN_QUOTE
		|| state == STATE_GENERAL)
		return (1);
	else
		return (0);
}

int	is_same_operator(char c, char operator, int i)
{
	if ((c == '<' || c == '>') && c == operator && i < 2)
		return (1);
	else
		return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}
