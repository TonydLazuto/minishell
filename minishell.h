/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:02:12 by aderose           #+#    #+#             */
/*   Updated: 2021/09/16 10:02:13 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <stdbool.h>
# include "libft/libft.h"

/**
 * BREAK ;
 * AND_IF &&
 * OR_IF ||
 * BRACKET (
 * 
 * 
 * PIPE |
 * OUTPUT_REDI >
 * INPUT_REDI <
 * APPEND >>
 * RD_UNTIL <<
 */

enum e_ntype
{
	BREAK = 0,
	AND_IF = 1,
	OR_IF = 2,
	BRACKET = 3,
	CMD = 4
};

enum e_cmdtype
{
	END = 0,
	PIPE = 1,
	INPUT_REDI = 2,
	OUTPUT_REDI = 3,
	APPEND = 4,
	RD_UNTIL = 5
};

typedef struct s_cmd
{
	char			**arg;
	int				pipefd[2];
	enum e_cmdtype	type;
}				t_cmd;

typedef struct s_node
{
	enum e_ntype	ntype;
	t_cmd			cmd;
	struct s_node	*parent;
	struct s_node	*right;
	struct s_node	*left;
}				t_node;

t_node	*new_node(enum e_ntype ntype);
void	rewind_tree(t_node **node);
void	clear_node(t_node *node);
t_node	*push_right(t_node *parent, enum e_ntype ntype,
					const char **arg, enum e_cmdtype type);
t_node	*push_left(t_node *parent, enum e_ntype ntype,
					const char **arg, enum e_cmdtype type);
t_node	*lastnode(t_node *node);

void	ft_exit(t_node *node, char *err);
void	printnodes(t_node *mynode);

t_node	*set_node_cmd(t_node *node, const char **arg, enum e_cmdtype type);
void	pipes(t_node *node, char **env);

#endif