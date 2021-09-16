.PHONY		= all clean fclean re bonus

NAME		= minishell

LIB			= libft.a

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

$(LIB):
				$(MAKE) --silent -C $(LIB_DIR)

$(NAME): 		$(OBJS) $(LIB)
				$(CC) -o $(NAME) $(OBJS) -L$(LIB_DIR) -lft

$(OBJ_DIR)/%.o:	%.c
				@ $(shell mkdir -p $(OBJ_DIR))
				$(CC) $(CFLAGS) -c $< -o $@

libclean:		
				$(MAKE) clean -C $(LIB_DIR)

libfclean:		libclean
				$(RM) $(LIB_DIR)/$(LIB)

clean:			libclean
				rm -rf $(OBJ_DIR)

fclean:			clean
				$(RM) $(LIB_DIR)/libft.a
				$(RM) $(NAME)

re:				fclean all
