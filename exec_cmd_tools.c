/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:10:35 by aderose           #+#    #+#             */
/*   Updated: 2021/12/16 17:51:16 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(t_list *node)
{
	t_token	*tk_next;
	t_token	*tk_prev;

	tk_next = get_next_token(node);
	tk_prev = get_prev_token(node);
	if ((tk_next && tk_next->type == TK_PIPE)
		|| (tk_prev && tk_prev->type == TK_PIPE))
		return (1);
	return (0);
}

void	check_tilde_replace(t_token *tk, int i, t_msh *msh)
{
	int		line;
	char	*path;
	char	*tmp;

	tmp = tk->arg[i];
	line = get_env_line(msh->myenv, "HOME");
	path = NULL;
	if (line == -1)
	{
		ft_putendl_fd("Error: HOME doesn't exist.", 1);
		return ;
	}
	path = ft_strchr(msh->myenv[line], '=');
	if (!path || *path == '\0' || *path++ == '\0')
	{
		ft_putendl_fd("Error: HOME have no value.", 1);
		return ;
	}
	tk->arg[i] = ft_strdup(path);
	ft_free(&tmp);
}

void	get_tilde(t_msh *msh)
{
	t_list	*cpy;
	t_token	*tk;
	int		i;

	i = 0;
	cpy = msh->node;
	while (cpy)
	{
		tk = (t_token *)msh->node->content;
		while (tk->arg && tk->arg[i])
		{
			if (tk->type == TK_CMD)
				check_env_intero(tk);
			if (tk->arg[i][0] == '~')
				check_tilde_replace(tk, i, msh);
			i++;
		}
		cpy = cpy->next;
	}
}
