.PHONY		= all clean fclean re bonus

NAME		= libft.a

HEADER		= libft.h

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= /bin/rm -f

SRCS		= ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_calloc.c ft_toupper.c ft_tolower.c ft_strmapi.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRCS_BONUS 	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

all: 		$(NAME)

$(NAME): 	$(OBJS)
			ar rc $(NAME) $(OBJS)
			ranlib $(NAME)

bonus:		$(OBJS) $(OBJS_BONUS)
			ar rc $(NAME) $(OBJS) $(OBJS_BONUS)
			ranlib $(NAME)

%.o: 		%.c $(HEADER)
			$(CC) -c $(CFLAGS) $< -o $(<:.c=.o)

clean:
			$(RM) $(OBJS)
			$(RM) $(OBJS_BONUS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

help: 
	@echo "Usage :"
	@echo "\tmake all : Rule NAME"
	@echo "\tmake (NAME) : Construction of libft.a."
	@echo "\tmake .c.o : Define the conversion from .c to .o."
	@echo "\tmake clean: Delete all objects files."
	@echo "\tmake fclean: Rule clean + delete also the library file."
	@echo "\tmake re: Rule fclean + all."
