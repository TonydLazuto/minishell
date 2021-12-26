/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:05:59 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/08 13:07:15 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_state(char c)
{
	if (c == '\'')
		return (STATE_IN_QUOTE);
	else if (c == '\"')
		return (STATE_IN_DQUOTE);
	else if (is_operator(c))
		return (STATE_IN_OPERATOR);
	else if (c == '\0')
		return (STATE_NULL);
	else if (c == ' ')
		return (STATE_SPACE);
	else
		return (STATE_GENERAL);
}

int	get_tk_type(char *c)
{
	if (is_operator(*c))
	{
		if (*c == '<')
		{
			if (ft_strlen(c) == 1)
				return (TK_IN_REDIR);
			else
				return (TK_HERE_DOC);
		}
		else if (*c == '>')
		{
			if (ft_strlen(c) == 1)
				return (TK_OUT_REDIR);
			else
				return (TK_OUT_DREDIR);
		}
		else
			return (TK_PIPE);
	}
	else
		return (TK_WORD);
}

int	get_cut(enum e_state state, char *input)
{
	int	i;

	i = 1;
	if (state == STATE_GENERAL)
		while (input[i] && input[i] != ' ' && !is_operator(input[i])
			&& input[i] != '\"' && input[i] != '\'')
			i++;
	else if (state == STATE_IN_OPERATOR)
		while (is_same_operator(input[i], *input, i))
			i++;
	else if (state == STATE_IN_QUOTE)
	{
		while (input[i] && input[i] != '\'')
			i++;
		if (input[i] == '\'')
			i++;
	}
	else if (state == STATE_IN_DQUOTE)
	{
		while (input[i] && input[i] != '\"')
			i++;
		if (input[i] == '\"')
			i++;
	}
	return (i);
}

void	tokenization(char *input, t_list **node)
{
	int				i;
	t_token			*token;
	enum e_state	state;
	char			*tmp;

	i = 0;
	while (*input == ' ')
		input++;
	if (!*input)
		return ;
	state = get_state(*input);
	i += get_cut(state, input);
	tmp = ft_substr(input, 0, i);
	token = new_token(tmp, get_tk_type(tmp));
	if (!token)
		ft_error(node, "malloc failed");
	ft_lstadd_back(node, ft_lstnew(token));
	if (is_in_word(state) && get_state(input[i]) == STATE_SPACE)
	{
		token = new_token(ft_strdup(" "), TK_WHITE_SPACE);
		if (!token)
			ft_error(node, "malloc failed");
		ft_lstadd_back(node, ft_lstnew(token));
	}
	tokenization((input + i), node);
}
