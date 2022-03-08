/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:31:43 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/07 14:08:36 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*set_list(char **arg, int is_space_ended)
{
	t_list	*result;
	int		i;

	result = NULL;
	i = 0;
	while (arg[++i])
	{
		ft_lstadd_back(&result, ft_lstnew(
				new_token(ft_strdup(" "), TK_WHITE_SPACE)));
		ft_lstadd_back(&result, ft_lstnew(
				new_token(arg[i], TK_WORD)));
	}
	if (is_space_ended)
		ft_lstadd_back(&result, ft_lstnew(
				new_token(ft_strdup(" "), TK_WHITE_SPACE)));
	return (result);
}

void	insert_list(t_list *new, t_list *lst)
{
	t_list	*tmp;

	tmp = ft_lstlast(new);
	if (lst->next)
		lst->next->prev = tmp;
	tmp->next = lst->next;
	lst->next = new;
	new->prev = lst;
}

void	cut_space(t_list *node)
{
	t_token	*tk;
	char	**arg;
	int		is_space_ended;

	tk = (t_token *)node->content;
	arg = ft_split(tk->value, ' ');
	if (tk->value[ft_strlen(tk->value) - 1] == ' ')
		is_space_ended = 1;
	else
		is_space_ended = 0;
	free(tk->value);
	tk->value = arg[0];
	insert_list(set_list(arg, is_space_ended), node);
	free(arg);
}
