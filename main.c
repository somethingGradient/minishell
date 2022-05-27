#include "minishell.h"

int	ft_exit(char *err_msg, int exit_code)
{
	if (err_msg)
		ft_putstr_fd(err_msg, 2);
	exit(exit_code);
}

void	free_char_array(char **array)
{
	int	i;

	i = -1;
	if (array)
	{
		while (array[++i] != NULL)
		{
			free(array[i]);
			array[i] = NULL;
		}
	}
	else
		return ;
	free(array);
	array = NULL;
}

void	ft_clear_data(t_general *general)
{
	if (general)
	{
		free_char_array(general->env);
		free_char_array(general->paths);
		free_char_array(general->commands);
		if (general->title)
			free(general->title);
		if (general->line)
			free(general->line);
		free(general);
		general = NULL;
	}
}

void	sig_handler(int signal)
{
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

int	minishell(t_general *general)
{
	// general->line = ft_strdup("abc");

	read_history("history");
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	while (1337)
	{
		general->line = readline(general->title);
		general->line[ft_strlen(general->line)] = '\0';
		if (general->line && *(general->line))
		{
			add_history(general->line);
			if (pre_parser_main(general->line) != 0)
			{
				ft_putstr_fd("Error.\nLine is a not closed.\n", 2);
				continue ;
			}
			else
			{
				split_cmd(general, general->line, 0);
				run_commands(general);
			}
			write_history("history");
		}
	}
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_general	*general;

	general = NULL;
	general = (t_general *)malloc(sizeof(*general));
	general->paths = NULL;
	general->env = NULL;
	general->title = NULL;
	general->line = NULL;
	general->commands = NULL;
	general->out_fd = STDOUT_FILENO;
	general->in_fd = STDIN_FILENO;
	general->env = copy_env(env);
	general->title = get_title(NULL);
	general->paths = get_env_paths(general->env);
	if (!general || !general->env || !general->title || !general->paths)
	{
		ft_clear_data(general);
		ft_putstr_fd("Error in setupping variables.", 2);
		exit(EXIT_FAILURE);
	}
	minishell(general);
	ft_clear_data(general);
    exit(EXIT_SUCCESS);
}
