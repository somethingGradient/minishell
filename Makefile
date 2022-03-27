
NAME	=	minishell

LIBNAME =	minishell.a

INCLUDES =	-lreadline

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror

LDFLAGS		= "-L/Users/akitty/.brew/opt/readline/lib"
CPPFLAGS	= "-I/Users/akitty/.brew/opt/readline/include"


SRC		=	main.c \
			pre_parser.c env_functions.c \
			get_title.c	ft_echo.c ft_cd.c \
			

OBJ		=	$(SRC:.c=.o)

LIBFT_PATH	=	./libft

LIBFT		=	libft/libft.a

.SILENT: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) $(OBJ) $(LIBFT) -lreadline $(LDFLAGS) -o $(NAME) 

#$(MAKE) all -C $(LIBFT_PATH)

%.o: %.c
		@$(CC) -c -o $@ $< $(CPPFLAGS)
clean:
		rm -rf $(OBJ)

#$(MAKE) clean -C $(dir $(LIBFT))
		
fclean: clean
		rm -rf $(NAME)

#$(MAKE) fclean -C $(dir $(LIBFT))
		

re: fclean all

.PHONY: all clean fclean re
