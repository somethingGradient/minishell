// clear && gcc main.c get_title.c libft/libft.a -lreadline && ./a.out
//clear && gcc main.c get_title.c libft/libft.a -lreadline && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./a.out

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>

/* for Linux */
//#include "/usr/include/readline/readline.h"
//#include "/usr/include/readline/history.h" 

/* for Mac */
 #include <readline/readline.h>
 #include <readline/history.h>

# define D_QUOTE '\"'
# define QUOTE '\''
# define D_QUOTE_S "\""
# define QUOTE_S "\'"

# define ERROR_PIPE "minishell: syntax error near unexpected token `|'\n"
# define ERROR_DIR "No such file or directory\n"
# define ERROR_HOME "minishell: cd: HOME not set\n"
# define ERROR_CMD "command not found\n"

#define BLOD  "\001\033[1m\002"						// Подчеркнуть, жирным шрифтом, выделить
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"	// x: background, y: foreground
#define CLOSE "\001\033[0m\002"						// Закрыть все свойства

int	g_ret_number;

typedef struct s_token
{
	char	*to_print;
	char	*to_exec;
	char	quote;
	char	*end;
	char	*new;
	int		i;
	int		init;
	int		len;
	int		posic;
}			t_token;

typedef struct s_split
{
	int		n_comand;
	int		ini;
	int		len;
	int		quote;
	int		qtt_pipe;
}			t_split;

typedef	struct s_general
{
	char	**env;

	char	**paths;

	char	*title;
	char	*line;

	char	**split_line;
	char	*cmd;
	int		exit_code;
	char	**path;
	bool	is_builtin;
	char	*name_file;
	char	*error_name_file;
	char	*home;
	char	**tokens;
	int		index_cmd;
	char	*commands[50];
	int		last_redir;
	int		out_fd;
	int		in_fd;
	int		is_append;
	bool	has_flag;
	t_split	split;
	t_token	token;

}	t_general;




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

// New split funcs
void	run_commands(t_general *general);
void	run_commands_aux(t_general *general);
void	action(t_general *general);
void	exec_process(t_general *general, int in, int out);
//void	ft_execve_pipe(t_general *general, int i, char *command);
void	split_cmd(t_general *general, char *in, int i);
void	init_split_struct(t_general *general);
char	*clean_spaces(char *in);
int		count_pipe(t_general *general, char *in, int i);




int	ft_exit(char *msg, int exit_code);
int	ft_export(t_general *general);
char *get_title(char *cwd);
void	tokenizer_clean_quotes(t_general *general, char *in);
int	fixing_for_norminette(t_general *general, char c, char *aux, int nbr);
int	tokenizer_find_char(char *string, char needle);
void	tokenizer(t_general *general);
void	split_cmd(t_general *general, char *in, int i);
void	init_split_struct(t_general *general);
char	*clean_spaces(char *in);
int	count_pipe(t_general *general, char *in, int i);
void	run_commands(t_general *general);
void	run_commands_aux(t_general *general);
void	action(t_general *general);
void	exec_process(t_general *general, int in, int out);
void	ft_execve_pipe(t_general *general, int i, char *command);
int	file_descriptor_handler(int in, int out);
void	spaces_in_pipe(t_general *general, int i, char *command);
void	execve_error(t_general *general);

void	is_builtin(char *cmd, t_general *general);
void	run_builtin(t_general *general);
void	free_char_array2(char **array);
void	free_char_array(char **array);
void	finish_tokenizer(t_general *general, t_token *tk);
void	free_tk(t_token *tk);
t_token	*init_tk(void);
void	get_dollar_sign(t_general *general, t_token *tk);
void	get_home_sign(t_general *general, t_token *tk);
void	ft_exit2(t_general *general);




// redir_out.c
int		redirect_out(t_general *general, int j);
int		simple_redir_out(t_general *general, int j, int flags);
int		find_char(char *string, char needle);

// redir_in.c
int		redirect_in(t_general *general, int j, char *aux);
char	**double_redir(t_general *general, char **file, int j);
void	read_until(char *end);
char	*new_comman(int i, char **str);


#endif