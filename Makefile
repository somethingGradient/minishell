
NAME	=	minishell

INCLUDES =	-lreadline

HEADER = minishell.h

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror

LDFLAGS		= "-L/Users/jannabel/.brew/opt/readline/lib"
CPPFLAGS	= "-I/Users/jannabel/.brew/opt/readline/include"


SRC		=	main.c \
			env_functions.c print_env_var.c \
			get_title.c	ft_echo.c ft_cd.c \
			ft_export.c pre_parser.c \
			builtins.c redir_in.c  \
			run_pipe_aux.c run_pipe.c split_cmd.c \
			token.c token_utils.c redir_out.c \
			ft_unset.c pre_parser_utils.c utils.c \
			signal.c env_functions2.c
			

OBJ		=	$(SRC:.c=.o)

LIBFT_PATH	=	libft/

LIBFT		=	libft/libft.a

.SILENT: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
		#$(MAKE) all -C $(LIBFT_PATH)
		#@$(CC) $(OBJ) $(LIBFT) -lreadline $(LDFLAGS) -o $(NAME) # for Mac
		@$(CC) -g $(OBJ) $(LIBFT) -lreadline -o $(NAME)  #for Linux
		

#$(MAKE) all -C $(LIBFT_PATH)

%.o: %.c $(HEADER)
		@$(CC) -c -o $@ $< $(CPPFLAGS)

clean:
		#@$(MAKE) clean -C $(dir $(LIBFT))
		@rm -rf $(OBJ)
		
fclean: clean
		#@$(MAKE) fclean -C $(dir $(LIBFT))
		@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
