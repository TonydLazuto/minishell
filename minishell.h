/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:02:12 by aderose           #+#    #+#             */
/*   Updated: 2021/11/19 18:56:37 by aderose          ###   ########.fr       */
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

enum e_node_type
{
	NODE_PIPE,
	NODE_IN_REDIR,
	NODE_OUT_REDIR,
	NODE_OUT_DREDIR,
	NODE_WORD,
	NODE_OR,
	NODE_AND,
	NODE_HERE_DOC
};

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*back;
}				t_env;

typedef struct s_cmd
{
	char	**arg;
	int		pipefd[2];
	int		len; // while arg[i]
	t_env	*env;
}				t_cmd;

typedef struct s_astNode
{
	t_cmd				cmd;
	enum e_node_type	type;
	struct s_astNode	*parent;
	struct s_astNode	*right;
	struct s_astNode	*left;
}						t_astnode;

int		get_next_line(int fd, char **line);
void	my_free(char **s);
size_t	my_strlen(const char *str);
char	*strjoinfree(char *s1, char *s2);
char	*my_strdup(char *s1);
char	*my_substr(char *s, unsigned int start, size_t len);
int		my_strncmp(char *s1, char *s2);

void	clearnodes(t_astnode **node);
void	nodeadd_right(t_astnode **anode, char *arg[],
			int type, t_env *env);

void	ft_error(t_astnode *node, char *err);
void	printnodes(t_astnode *mynode);

int		launch_builtin(t_astnode *node);
void    ft_env(t_astnode *node);
void	ft_export(t_astnode *node);

void	exec_cmd(t_astnode *node, char **env);
void	parent_pipe(t_astnode *node);
void	child_out_redi(t_astnode *node);
void	child_pipe(t_astnode *node);

void	clear_env(t_env **env);
void	envadd_back(t_env **aenv, char *name, char *value);
t_env	*envlast(t_env *env);
int		get_env_size(t_env *env);
t_env	*pop_env(t_env *env, char *name);
t_env	*get_env_by_name(t_env *env, char *name);
t_env   *get_linked_list(char **envp);

int		is_builtin(t_astnode *node);
void	ft_cd(t_astnode *node);
void	ft_echo(t_astnode *node);
void	ft_pwd(t_astnode *node);
void    ft_env(t_astnode *node);
void	ft_export(t_astnode *node);
void    export_no_args(t_astnode *node);
void	ft_unset(t_astnode *node);


#endif
