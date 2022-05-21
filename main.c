#include "minishell.h"

int	ft_exit(char *msg, int exit_code)
{
	if (msg)
		ft_putstr_fd(msg, 3);
	exit(exit_code);
}

void	ft_exit2(t_general *general)
{
	free_char_array2(general->commands);
	if (general->path)
		free_char_array(general->path);
	free (general->home);
	printf("exit\n");
	exit(0);
}

void	free_char_array2(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
}

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
	}
	free(array);
}

void	ft_clear_data(t_general *general)
{
	int		i;
	char	*temp;

	if (general)
	{
		if (general->env)
		{
			i = -1;
			while (general->env[++i])
				free(general->env[i]);
			free(general->env);
		}
		if (general->paths)
		{
			i = -1;
			while (general->paths[++i])
				free(general->paths[i]);
			free(general->paths);
		}
		if (general->title)
			free(general->title);

		
		if (general->commands[0])
		{
			i = -1;
			while (general->commands[++i])
				free(general->commands[i]);
		}	



		// if (general->cmd)
		// 	free(general->cmd);
		// if (general->split_line)
		// {
		// 	i = -1;
		// 	while (general->split_line[++i])
		// 		free(general->split_line[i]);
		// 	free(general->split_line);
		// }
		
		
		free(general);
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
	char	*title;


	general->line = ft_strdup("alo");



	// read_history("history");
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");
	// while (1337)
	// {
	// 	general->out_fd = STDOUT_FILENO;
	// 	general->in_fd = STDIN_FILENO;
		
	// 	general->line = readline(general->title);
	// 	general->line[ft_strlen(general->line)] = '\0';

		if (general->line && *(general->line))
		{
			// add_history(general->line);
			// if (pre_parser_main(general->line) != 0)
			// {
			// 	ft_putstr_fd("Error.\nNot closed quotes.\n", 1);
			// 	continue ;
			// }
			split_cmd(general, general->line, 0);
			run_commands(general);



		}

	free(general->line);
	// 	if (!general->line)
	// 	{
	// 		ft_putstr_fd("exit\n", 1);
	// 		return (0);
	// 	}
	// 	// write_history("history");
	// }

	// if (general->line)
	// 	free(general->line);
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
	general->cmd = NULL;
	general->split_line = NULL;

	general->env = copy_env(env);
	general->title = get_title(NULL);
	general->paths = get_env_paths(general->env);

	minishell(general);

	ft_clear_data(general);
    return (0);
}
