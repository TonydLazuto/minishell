.PHONY		= all clean fclean re bonus libclean libfclean

NAME		= minishell

LIBA		= libft.a

LIB_DIR		= libft

FLAGS		= -L libft -lft -lreadline

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= /bin/rm -f

INC			= minishell.h

OBJ_DIR		= obj

SRCS		=	builtin.c \
				builtin2.c \
				check_path.c \
				env_list.c \
				env_list2.c \
				exec_cmd.c \
				exec_checker.c \
				export.c \
				export2.c \
				export_no_args.c \
				minishell.c \
				node.c \
				utils.c \
				redir.c \
				pipe.c

OBJS		= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: 			$(NAME)

$(NAME): 		$(OBJS)
				@make --silent -C $(LIB_DIR)
				$(CC) $(LIB_DIR)/$(LIBA) -o $(NAME) $(OBJS) $(FLAGS)

$(OBJ_DIR)/%.o:	%.c
				@mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@

libclean:		
				@make clean -C $(LIB_DIR)

libfclean:
				@make fclean -C $(LIB_DIR)

clean:			libclean
				rm -rf $(OBJ_DIR)

fclean:			clean
				$(RM) $(LIB_DIR)/$(LIBA)
				$(RM) $(NAME)

re:				fclean all
