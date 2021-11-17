/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bis.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:02:12 by aderose           #+#    #+#             */
/*   Updated: 2021/11/12 11:38:26 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
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

typedef struct s_cmd
{
	char	**arg;
	int		pipefd[2];
}				t_cmd;

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

/**
 * t_cmd *cmd;
 * cmd = malloc(sizeof(*t_cmd))
 * ou alors
 * t_cmd cmd;
 * cmd.arg = malloc(sizeof(char*) * (size + 1));
 */

typedef struct s_astNode
{
	t_cmd				cmd;
	enum e_tk_type		type;
	struct s_astNode	*parent;
	struct s_astNode	*right;
	struct s_astNode	*left;
}						t_astnode;

typedef struct s_token
{
	enum e_tk_type		type;
	char				*value;
}				t_token;

enum e_cmdtype
{
	END = 0,
	PIPE = 1,
	REDIR_IN = 2,
	REDIR_OUT = 3,
	APPEND = 4,
	RD_UNTIL = 5
};

enum e_var
{
	NONE = 0,
	VAR = 1,
};

int		get_next_line(int fd, char **line);
void	my_free(char **s);
size_t	my_strlen(const char *str);
char	*strjoinfree(char *s1, char *s2);
char	*my_strdup(char *s1);
char	*my_substr(char *s, unsigned int start, size_t len);
int		ft_strcmp(char *s1, const char *s2);

t_cmd	*new_cmd(char **arg, int type);
t_cmd	*cmdlast(t_cmd *cmd);
void	clearcmds(t_cmd **cmd);
void	cmdadd_back(t_cmd **acmd, char *arg[], int len);

void	ft_exit(t_cmd *cmd, char *err);
void	printcmds(t_cmd *mycmd);

int		check_builtin(t_cmd *cmd, char **env);
void	ft_export(t_cmd *cmd, char **env);

void	exec_cmd(t_cmd *cmd, char **env);
void	pipes(t_cmd *cmd, char **env);
t_cmd	*redir_out(t_cmd *cmd, char **env);
void	parent_pipe(t_cmd *cmd);
void	child_pipe(t_cmd *cmd);
void	child_redi(t_cmd *cmd);

#endif
