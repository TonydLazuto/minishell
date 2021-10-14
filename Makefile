.PHONY		= all clean fclean re bonus libclean libfclean

NAME		= minishell

LIBA		= libft.a

LIB_DIR		= libft

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= /bin/rm -f

INC			= minishell.h

OBJ_DIR		= obj

SRCS		=	minishell.c \
				cmd.c \
				pipe.c \
				redir_out.c \
				builtin.c \
				exec_cmd.c \
				utils.c

OBJS		= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: 			$(NAME)

$(NAME): 		$(OBJS)
				@make --silent -C $(LIB_DIR)
				$(CC) $(LIB_DIR)/$(LIBA) -o $(NAME) $(OBJS) -L$(LIB_DIR) -lft -lreadline

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
