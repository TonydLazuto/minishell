/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:17:52 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/07 17:49:05 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cut_and_join(t_list *node)
{
	t_list	*tmp;

	tmp = node->next;
	if (node->next)
	{
		if (node->next->next)
			node->next->next->prev = node;
		node->next = node->next->next;
	}
	else
	{
		node->next = NULL;
	}
	ft_lstdelone(tmp, &del_token);
}

int	is_redirection(enum e_tk_type type)
{
	if (type == TK_HERE_DOC)
		return (1);
	else if (type == TK_IN_REDIR)
		return (1);
	else if (type == TK_OUT_REDIR)
		return (1);
	else if (type == TK_OUT_DREDIR)
		return (1);
	else
		return (0);
}

t_token	*get_prev_token(t_list *node)
{
	if (!node)
		return (NULL);
	if (node->prev)
		return ((t_token *)node->prev->content);
	else
		return (NULL);
}

t_token	*get_next_token(t_list *node)
{
	if (!node)
		return (NULL);
	if (node->next)
		return ((t_token *)node->next->content);
	else
		return (NULL);
}

char	*fusion(char *str, t_env_var datas)
{
	int		len;
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	tmp = str;
	len = ft_strlen(str) + ft_strlen(datas.value) + ft_strlen(datas.rest);
	result = malloc(sizeof(char) * (len +1));
	if (!result)
		return (NULL);
	while (*str)
		*(result + i++) = *str++;
	while (*datas.value)
		*(result + i++) = *datas.value++;
	while (*datas.rest)
		*(result + i++) = *datas.rest++;
	*(result + i) = '\0';
	free(tmp);
	return (result);
}
