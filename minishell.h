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

#ifndef MINISHEL_H
# define MINISHEL_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>

typedef enum
{
	NODE_TYPE_FUNCTION_CALL = 1,
	NODE_TYPE_FUNCTION_DECL = 2,
	NODE_TYPE_STATEMENT = 3,
	NODE_TYPE_OPERAND = 4
} e_node_type;

typedef enum
{
	VAR_TYPE_VOID = 5,
	VAR_TYPE_INTEGER = 6
} e_var_type;

typedef struct s_node_info
{
	char	*name;
	int		type;
	int		size;
}				t_node_info;

typedef struct s_debug_info
{
	

}				t_debug_info;

typedef struct s_info
{
	int				type;
	t_node_info		*node_info;
	t_debug_info	*debug;
}				t_info;

typedef struct s_node
{
	t_info			info;
	struct s_node	*parent;
	struct s_node	*right;
	struct s_node	*left;
	
}				t_node;


t_node	*new_node(t_info info);
t_node	*push_right(t_node *node, t_info info);
t_node	*push_left(t_node *node, t_info info);
t_node	*push_parent(t_node *left, t_node *right, t_info info);
void	clear_node(t_node *node);

#endif