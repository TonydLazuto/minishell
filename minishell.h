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
 * PIPE |
 * OUTPUT_REDI >
 * INPUT_REDI <
 * APPEND >>
 * RD_UNTIL <<
 */

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
	int				type;
	int				pipefd[2];
	struct s_cmd 	*next;
	struct s_cmd 	*back;
}				t_cmd;


typedef struct s_node
{
	t_cmd			*cmd;
	struct s_node	*next;
	struct s_node	*back;
}				t_node;

int		get_next_line(int fd, char **line);
void	my_free(char **s);
size_t	my_strlen(const char *str);
char	*strjoinfree(char *s1, char *s2);
char	*my_strdup(char *s1);
char	*my_substr(char *s, unsigned int start, size_t len);

t_node	*new_node(t_cmd *cmd);
void	rewind_node(t_node **node);
void	clearnodes(t_node *node);
void	nodeadd_back(t_node **anode, t_cmd *cmd);

t_cmd	*new_cmd(char **arg, int type);
t_cmd	*cmdlast(t_cmd *cmd);
void	clearcmds(t_cmd **cmd);
void	cmdadd_back(t_cmd **acmd, char *arg[], int len);

void	ft_exit(t_node *node, char *err);
void	printcmds(t_cmd *mycmd);
void	printnodes(t_node *mynode);

t_node	*set_node_cmd(t_node *node, const char **arg, enum e_cmdtype type);
void	pipes(t_node *node, char **env);
void	output_redi(t_node *node, char **env);



#endif
