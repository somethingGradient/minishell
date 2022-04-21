
NAME	=	minishell

INCLUDES =	-lreadline

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror

LDFLAGS		= "-L/Users/akitty/.brew/opt/readline/lib"
CPPFLAGS	= "-I/Users/akitty/.brew/opt/readline/include"


SRC		=	main.c \
			pre_parser.c env_functions.c print_env_var.c \
			get_title.c	ft_echo.c ft_cd.c \
			ft_export.c pre_parser.c \
			builtins.c redir_in.c  \
			run_pipe_aux.c run_pipe.c split_cmd.c \
			token.c
			

OBJ		=	$(SRC:.c=.o)

LIBFT_PATH	=	libft/

LIBFT		=	libft/libft.a

.SILENT: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
		@$(MAKE) all -C $(LIBFT_PATH)
		@$(CC) -g $(OBJ) $(LIBFT) -lreadline -o $(NAME) # for Linux
		@$(CC) $(OBJ) $(LIBFT) -lreadline $(LDFLAGS) -o $(NAME) # for Mac
		

#$(MAKE) all -C $(LIBFT_PATH)

%.o: %.c
		@$(CC) -c -o $@ $< $(CPPFLAGS)

clean:
		@$(MAKE) clean -C $(dir $(LIBFT))
		@rm -rf $(OBJ)
		
fclean: clean
		@$(MAKE) fclean -C $(dir $(LIBFT))
		@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
