#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/ioctl.h>


/* for Linux */
// #include "/usr/include/readline/readline.h"
// #include "/usr/include/readline/history.h" 

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
#define true 1
#define false 0

# define GREEN "\001\033[1;49m\002"
# define BLUE "\001\033[1;96m\002"

int	g_ret_number;

typedef unsigned char bool;

typedef struct s_flags
{
	int	dobles_quotes;
	int	single_quotes;
	int	braces;
	int	backslash;
}	t_flags;

typedef struct s_token
{
	char	*to_print;
	char	*to_exec;
	char	*end;
	char	*new;
	char	quote;
	int		i;
	int		init;
	int		len;
	int		posic;
}	t_token;

typedef struct s_split
{
	int		n_comand;
	int		ini;
	int		len;
	int		quote;
	int		qtt_pipe;
}	t_split;

typedef	struct s_general
{
	char	**env;
	char	*title;
	char	**paths;
	char	*line;
	char	**commands;
	t_split	split;
	t_token	token;
	
	bool	is_builtin;
	char	*name_file;
	char	*error_name_file;
	char	*home;
	char	**tokens;
	int		index_cmd;
	
	int		last_redir;
	int		out_fd;
	int		in_fd;
	int		is_append;
	bool	has_flag;
}	t_general;

/* main.c */
void	get_title(t_general *general, char *cwd);
void	free_char_array(char **array);

/* pre_parser.c - запрещает многострочный режим */
int		pre_parser_main(char *str);
void	pre_parser(char *str, t_flags *flags);

/* split_cmd.c - считает количество команд */
void	split_cmd(t_general *general, char *in, int i);

/* run_pipe.c - запускает команды */
void	run_commands(t_general *general);

/* run_pipe_aux.c */
int		file_descriptor_handler(int in, int out);
void	spaces_in_pipe(t_general *general, int i, char *command);
void	execve_error(t_general *general);

/* redir_out.c - инициализирует поток вывода */
int		redirect_out(t_general *general, int j);

/* redir_in.c - инициализирует поток ввода */
int		redirect_in(t_general *general, int j, char *aux);

/* token.c - разделяет команды */
void	tokenizer(t_general *general);

/* signal.c - обработчик сигналов*/
void	ft_sighandler(int signum, siginfo_t *sig, void *context);

/* token_utils.c */
t_token	*init_tk(void);
void	finish_tokenizer(t_general *general, t_token *tk);
int		tokenizer_find_char(char *string, char needle);
void	tokenizer_clean_quotes(t_general *general, char *in);

/* ENV FUNCTIONS */
char	**copy_env(char	**env);
char	*ft_get_env(char **env, char *str);
char	**get_env_paths(char **env);
void	change_env(char	**env, char *key, char *value);
void	ft_show_env(char **env, int out_fd);
int		print_env_var(t_general *general, char *str, int *i);

/* BUILTINS */
	/* builtins.c */
void	is_builtin(char *cmd, t_general *general);
void	run_builtin(t_general *general);
void	ft_cd(t_general *general);
void	ft_pwd(t_general *general);
int		ft_echo(t_general *general);
void	ft_unset(t_general *general);
void	ft_export(t_general *general);
void	get_title(t_general *general, char *cwd);

void	ft_clear_data(t_general *general);


int	file_descriptor_handler(int in, int out);
void	spaces_in_pipe(t_general *general, int i, char *command);
void	execve_error(t_general *general);

void	is_builtin(char *cmd, t_general *general);
void	run_builtin(t_general *general);
void	free_char_array(char **array);



void	run_signals();


/* SIGNALS */
void	signal_ctlc(int sig);
void	signal_ctlc_heredoc(int sig);
int		termios_change(bool echo_ctl_chr);



#endif