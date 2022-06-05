# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akitty <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/04 19:48:18 by akitty            #+#    #+#              #
#    Updated: 2022/06/04 19:48:21 by akitty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

INCLUDES	=	-lreadline

HEADER		=	minishell.h

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

SRC			=	main.c \
				env_functions.c print_env_var.c \
				get_title.c	ft_echo.c ft_cd.c \
				ft_export.c pre_parser.c \
				builtins.c redir_in.c  \
				run_pipe_aux.c run_pipe.c split_cmd.c \
				token.c token_utils.c redir_out.c \
				ft_unset.c pre_parser_utils.c utils.c \
				signal.c	

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
		@$(MAKE) all -C $(LIBFT_PATH)
		@$(CC) -g $(FLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
		@echo Compiled!
	

%.o: %.c $(HEADER)
		@$(CC) $(FLAGS) -c -o $@ $< $(CPPFLAGS)

clean:
		@$(MAKE) clean -C $(dir $(LIBFT))
		@rm -rf $(OBJ)
		@echo Cleaned!
		
fclean: clean
		@$(MAKE) fclean -C $(dir $(LIBFT))
		@rm -rf $(NAME)
		@echo Full cleaned!

re: fclean all

.PHONY: all clean fclean re
