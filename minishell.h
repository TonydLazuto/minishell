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

enum e_node_type
{
	NODE_PIPE,
	NODE_IN_REDIR,
	NODE_OUT_REDIR,
	NODE_OUT_DREDIR,
	NODE_CMD,
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
	int		len;
	int		exit_status;
	t_env	*env;
}				t_cmd;

typedef struct s_node
{
	t_cmd				cmd;
	enum e_node_type	type;
	struct s_node		*back;
	struct s_node		*next;
}						t_node;

void	ft_error(t_node *node, char *err);
void	printnodes(t_node *mynode);
int		my_strncmp(char *s1, char *s2);
char	*strjoinfree(char *s1, char *s2);
void	ft_free(char **s);

void	clearnodes(t_node **node);
void	nodeadd_back(t_node **anode, char *arg[],
			int type, t_env *env);

int		check_both_pipe_cmd(t_node *node);
int		check_pipe(t_node *node);
int		check_cmd(t_node *node);
int		check_without_fork(t_node *node);

void	parent_pipe(t_node *node);
void	child_append(t_node *node);
void	child_out_redir(t_node *node);
void	child_in_redir(t_node *node);
void	child_pipe(t_node *node);
void	exec_cmd(t_node *node, char **env);
void	check_relatif_path(t_node *node, char **mycmd);

void	clear_env(t_env **env);
void	envadd_back(t_env **aenv, char *name, char *value);
t_env	*envlast(t_env *env);
int		get_env_size(t_env *env);
t_env	*pop_env(t_env *env, char *name);
t_env	*get_env_by_name(t_env *env, char *name);
t_env	*get_linked_list(char **envp);

int		launch_builtin(t_node *node);
int		is_builtin(t_node *node);
void	ft_cd(t_node *node);
void	ft_echo(t_node *node);
void	ft_pwd(t_node *node);
void	ft_env(t_node *node);
void	ft_export(t_node *node);
void	export_append(t_node *node);
void	export_normal(t_node *node);
void	export_no_args(t_node *node);
void	ft_unset(t_node *node);
void	ft_exit(t_node *node);

#endif
