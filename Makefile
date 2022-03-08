# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/14 15:16:41 by jdidier           #+#    #+#              #
#    Updated: 2021/12/16 17:07:11 by jdidier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

CC=gcc

CFLAGS= -Wall -Wextra -Werror

FLAGS= -L libft -lft -lreadline 

HEADERS=minishell.h libft/libft.h

RM=rm -f

SRCS= main.c lexer.c lexer_tools.c parser.c parser_tools.c exit.c \
utils.c get_set_env.c cut_space.c builtin.c builtin_tools.c builtin2.c \
check_path.c exec_cmd_tools.c exec_cmd.c export.c export2.c env_tools.c env_tools2.c\
redir.c redir_tools.c pipe.c check_syntax.c global.c heredoc.c parser2.c parser3.c signal.c

SRCS_BONUS=

OBJS=	${SRCS:.c=.o}

BONUS=	${SRCS_BONUS:.c=.o}

all:	${NAME}

${NAME}:	${OBJS} ${HEADERS}
			@make --silent -C libft all
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${FLAGS}

%.o:	%.c
		${CC} ${CFLAGS} -c $< -o $@

clean:
		@make -C libft clean
		${RM} ${OBJS} 

fclean: clean
		${RM} libft/libft.a
		${RM} ${NAME}

re: fclean all

.PHONY: clean fclean re all
