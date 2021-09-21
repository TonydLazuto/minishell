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

# define TYPE_PIPE 0
# define TYPE_IN_DIR 1
# define TYPE_OUT_DIR 2

typedef struct s_arg
{
	char	*name;
	int		type;
	int		size;
}				t_arg;

typedef struct s_node
{
	t_arg			*arg;
	int				type;
	struct s_node	*parent;
	struct s_node	*right;
	struct s_node	*left;
}				t_node;

t_node	*new_node(int type, t_arg *arg);
t_node	*push_right(t_node *node, int type);
t_node	*push_left(t_node *node, int type);
void	rewind_tree(t_node **node);
void	clear_node(t_node *node);
t_node	*find_arg(t_node *node, char *arg);

#endif