/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:15:49 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/17 17:18:24 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
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
	TK_WHITE_SPACE,
	TK_WORD,
	TK_CMD,
	TK_HERE_DOC,
	TK_IN_REDIR,
	TK_OUT_REDIR,
	TK_OUT_DREDIR,
	TK_PIPE,
};

int		g_exit_status;

typedef struct s_msh
{
	pid_t	*pid;
	t_list	*node;
	char	**myenv;
	int		save_stdout;
	int		save_stdin;
	int		nb_cmds;
}				t_msh;

typedef struct s_token
{
	int				len;
	enum e_tk_type	type;
	char			*value;
	char			**arg;
	int				pipefd[2];
}					t_token;

typedef struct s_env_var
{
	char	*value;
	char	*rest;
}			t_env_var;

int		is_operator(char c);
int		is_same_operator(char c, char operator, int i);
int		is_in_word(enum e_state state);
int		is_redirection(enum e_tk_type type);
void	tokenization(char *str, t_list **node);
void	ft_error(t_list **list, char *str);
int		parser(t_list **node, char **env, t_msh *msh);
t_token	*get_next_token(t_list *node);
t_token	*get_prev_token(t_list *node);
char	*get_env(char *str, char **envp);
void	del_token(void *token);
int		get_tk_type(char *c);
t_token	*new_token(char *str, enum e_tk_type type);

void	replace_env(char **str, char **env, t_msh *msh);
void	get_set_env(t_list *node, char **env, t_msh *msh);
void	parse_word(t_list *node);
void	erase_space(t_list *node);
char	*fusion(char *str, t_env_var d_env_var);
void	cut_space(t_list *node);
void	cut_and_join(t_list *node);

char	**env_cpy(char **envp);
int		get_env_line(char **env, char *name);
char	**env_after_unset(char **env, int line);
char	**env_add(char **env, char *line);
char	*replace_env_line(char *line, char *new_line);
char	*join_env_value(char *line, char *name, char *value);
char	*get_env_value(char *name, char **env, t_msh *msh);
void	free_myenv(char **myenv);

void	export_new(t_msh *msh, char *arg, char *name);
void	modify_export(t_msh *msh, int line, char *arg);
void	print_export(t_msh *msh);
void	ft_export(t_msh *msh);
void	ft_unset(t_msh *msh, t_token *tk);
void	ft_echo(t_list *node);
void	ft_pwd(t_list *node);
void	ft_env(t_msh *msh);
void	ft_exit(t_msh *msh);
void	ft_cd(t_msh *msh);

int		check_path(t_msh *msh, char **mycmd);
int		check_pipe(t_list *node);

void	ft_error_msh(t_msh *msh, char *str);
int		is_builtin(t_token *tk);
void	launch_builtin(t_msh *msh);
void	child_node(t_list *node, char **envp);
void	parent_node(t_list *node);

void	child_pipe(t_list *node);
void	parent_pipe(t_list *node);
void	no_pipe(t_msh *msh);
void	multiple_cmds(t_msh *msh);

char	*apply_redir(t_list *node);
char	*redir_in(t_list *node, char *err_msg_fd, int *redir_in_done);
char	*redir_out(t_list *node, char *err_msg_fd, int *redir_out_done);
char	*redir_append(t_list *node, char *err_msg_fd, int *redir_out_done);
char	*redir_heredoc(t_list *node, char *err_msg_fd, int *redir_in_done);
void	get_tilde(t_msh *msh);
void	try_redirs(t_list *node);

void	ft_free(char **s);
char	*strjoinfree(char *s1, char *s2);
void	run_exec(t_msh *msh);

int		check_syntax_redir(t_list *tokens);
int		check_syntax_pipe(t_list *node);

void	set_stdio(t_msh *msh);
void	unset_stdio(t_msh *msh);
void	set_global(t_msh *msh);
void	init_pids_pipes(t_msh *msh);

void	check_env_intero(t_token *tk);
int		get_nb_args(t_list *node);
char	**set_arg(t_list *node);
void	simplification_redir(t_list *node);
void	heredoc(char *delemiter);
void	get_heredoc(t_list *node);
void	parent_signal(int sig);
void	child_signal(int sig);

#endif