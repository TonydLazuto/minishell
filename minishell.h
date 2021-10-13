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
	REDIR_IN = 2,
	REDIR_OUT = 3,
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

int		get_next_line(int fd, char **line);
void	my_free(char **s);
size_t	my_strlen(const char *str);
char	*strjoinfree(char *s1, char *s2);
char	*my_strdup(char *s1);
char	*my_substr(char *s, unsigned int start, size_t len);

t_cmd	*new_cmd(char **arg, int type);
t_cmd	*cmdlast(t_cmd *cmd);
void	clearcmds(t_cmd **cmd);
void	cmdadd_back(t_cmd **acmd, char *arg[], int len);

void	ft_exit(t_cmd *cmd, char *err);
void	printcmds(t_cmd *mycmd);

void	pipes(t_cmd *cmd, char **env);
void	redir_out(t_cmd *cmd, char **env);



#endif
