.PHONY		= all clean fclean re bonus libclean libfclean

NAME		= minishell

LIBA			= libft.a

LIB_DIR		= libft

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= /bin/rm -f

INC			= minishell.h

LIB_DIR		= libft

OBJ_DIR		= obj

SRCS		=	minishell.c \
				node.c \
				node2.c

OBJS		= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: 			$(NAME)

$(NAME): 		$(OBJS)
				@make --silent -C $(LIB_DIR)
				$(CC) $(LIB_DIR)/$(LIBA) -o $(NAME) $(OBJS) -L$(LIB_DIR) -lft

$(OBJ_DIR)/%.o:	%.c
				@mkdir -p $(OBJ_DIR)
				$(CC) -I$(LIB_DIR) -c $< -o $@

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
