// clear && gcc main.c get_title.c libft/libft.a -lreadline && ./a.out
//clear && gcc main.c get_title.c libft/libft.a -lreadline && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./a.out

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

/* for Linux */
#include "/usr/include/readline/readline.h"
#include "/usr/include/readline/history.h" 

/* for Mac */
// #include <readline/readline.h>
// #include <readline/history.h>

#define BLOD  "\001\033[1m\002"						// Подчеркнуть, жирным шрифтом, выделить
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"	// x: background, y: foreground
#define CLOSE "\001\033[0m\002"						// Закрыть все свойства

typedef	struct s_general
{
	char	**env;

	char	**paths;

	char	*title;
	char	*line;

	char	**split_line;
	char	*cmd;

	int		exit_code;

}	t_general;

int	ft_exit(char *msg, int exit_code);

int	ft_export(t_general *general);

char *get_title(char *cwd);


/* ENV FUNCTIONS */
char	**copy_env(char	**env);
char	*ft_get_env(char **env, char *str);
char	**get_env_paths(char **env);
void	change_env(char	**env, char *key, char *value);
void	ft_show_env(char **env);
int		print_env_var(t_general *general, char **str, int *i);

int	pre_parser_main(char *str);

/* BUILTINS */
int	ft_echo(t_general *general);
int	ft_cd(t_general *general);

int		ft_isalpha(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t n);
char	*ft_strdup(const char *s);
void	*ft_calloc(size_t n, size_t size);
int		ft_isprint(int c);
int		ft_isalnum(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(char *s1, char *s2);

#endif