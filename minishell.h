/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:15:49 by jdidier           #+#    #+#             */
/*   Updated: 2021/11/12 11:16:51 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>

enum e_state 
{
	STATE_GENERAL,
	STATE_IN_QUOTE,
	STATE_IN_DQUOTE,
	STATE_IN_WORD,
	STATE_IN_OPERATOR,
	STATE_SPACE,
	STATE_NULL
};

enum e_tk_type
{
	TK_PIPE,
	TK_IN_REDIR,
	TK_OUT_REDIR,
	TK_OUT_DREDIR,
	TK_WORD,
	TK_IN_BRAKET,
	TK_OUT_BRAKET,
	TK_OR,
	TK_AND,
	TK_HERE_DOC,
	TK_WHITE_SPACE
};

typedef struct s_astNode
{
	struct s_astNode	*parent;
	struct s_astNode	*right;
	struct s_astNode	*left;
}						t_astnode;

typedef struct s_token
{
	enum e_tk_type		type;
	char				*value;
}				t_token;

int		is_built_in(char *str);
void	tokenization(char *str, t_list **tokens);
void	parser(t_list *tokens);

#endif