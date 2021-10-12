/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:02:12 by aderose           #+#    #+#             */
/*   Updated: 2021/10/11 14:44:23 by aderose          ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# define BUFFER_SIZE 50

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
	int				len; // maybe nombre d'args
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

int				get_next_line(int fd, char **line);
void			my_free(char **s);
size_t			my_strlen(const char *str);
char			*strjoinfree(char *s1, char *s2);
char			*my_strdup(char *s1);
char			*my_substr(char *s, unsigned int start, size_t len);


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
void	output_redi(t_node *node, char **env);



#endif
