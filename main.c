#include "minishell.h"

int	ft_exit(char *msg, int exit_code)
{
	if (msg)
		ft_putstr_fd(msg, 3);
	exit(exit_code);
}

int	mk_cmd(t_general *general)
{
	char	*temp;
	int		i;
	char	c;

	if (*(general->cmd) == '\'' || *(general->cmd) == '"')
	{
		c = *(general->cmd);
		i = 0;
		while (general->cmd[i] == c)
			i++;
		general->cmd[ft_strlen(general->cmd) - i] = '\0';
		general->cmd += i;
	}
	if (!ft_strcmp(general->cmd, "echo") || !ft_strcmp(general->cmd, "cd")
		|| !ft_strcmp(general->cmd, "pwd") || !ft_strcmp(general->cmd, "env")
		|| !ft_strcmp(general->cmd, "exit") || !ft_strcmp(general->cmd, "export"))
		return (0);
	i = -1;
	if (access(general->cmd, F_OK) > -1)
		return (0);	
	general->paths = get_env_paths(general->env);
	while (general->paths[++i])
	{
		temp = general->cmd;
		general->cmd = ft_strjoin(general->paths[i], general->cmd);
		if (access(general->cmd, F_OK) > -1)
		{
			free(temp);
			return (0);
		}
		free(general->cmd);
		general->cmd = temp;
	}
	return (1);
}

void	ft_clear_data(t_general *general)
{
	int		i;
	char	*temp;

	if (general)
	{
		if (general->title)
			free(general->title);
		if (general->line)
			free(general->line);
		if (general->cmd)
			free(general->cmd);
		if (general->split_line)
		{
			i = -1;
			while (general->split_line[++i])
				free(general->split_line[i]);
			free(general->split_line);
		}
		if (general->paths)
		{
			i = -1;
			while (general->paths[++i])
				free(general->paths[i]);
			free(general->paths);
		}
		if (general->env)
		{
			i = -1;
			while (general->env[++i])
				free(general->env[i]);
			free(general->env);
		}
		free(general);
	}
}

int	command_fork(t_general *general)
{
	int status = 0;

	if (!ft_strcmp(general->cmd, "echo"))
		ft_echo(general);	
	else if (!ft_strcmp(general->cmd, "cd"))
		ft_cd(general);
	else if (!ft_strcmp(general->cmd, "pwd"))
	{
		char *temp;

		temp = ft_get_env(general->env, "PWD");
		ft_putstr_fd(temp, 1);
		free(temp);
		return (0);
	}
	else if (!ft_strcmp(general->cmd, "export"))
	{
		general->exit_code = ft_export(general);
		return (0);
	}
	else if (!ft_strcmp(general->cmd, "env"))
		ft_show_env(general->env);
	else if (!ft_strcmp(general->cmd, "exit"))
		return (0);
	else
	{
		int child = fork();
		
		if (child < 0)
			return (0);
		else if (child == 0)
		{
			if (execve(general->cmd, general->split_line, general->env)< 0)
			{
				printf("ERROR EXECVE.");
				return (-1);
			}
		}
		else
			waitpid(child, &(general->exit_code), 0);
	}
	return (status);
}

int	execute_cmd(t_general *general)
{
	char	*temp;
	char	*str;

	general->split_line = ft_split(general->line, ' ');
	if (!general->split_line)
		return (0);
	general->cmd = ft_strdup(general->split_line[0]);
	if (!general->cmd)
		return (0);
	if (mk_cmd(general))
	{
		printf("Command '%s' not found.\n", general->cmd );
		return (-1);
	}
	command_fork(general);
	return (0);
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

	read_history("history");
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");

	while (1)
	{
		/*general->line = readline(general->title);
		general->line[ft_strlen(general->line)] = '\0';

		if (general->line && *(general->line))
		{
			add_history(general->line);
			if (pre_parser_main(general->line) != 0)
			{
				ft_putstr_fd("Error.\nNot closed quotes.\n", 1);
				continue ;
			}
			execute_cmd(general);
		}
		if (!general->line)
		{
			ft_putstr_fd("exit\n", 1);
			return (0);
		}
		write_history("history");
		free(general->line);*/
		get_line(&general);
		if (general->line)
		{
			if (ft_strlen(general->line) != 0)
			{
				split_cmd(&general, general->line, 0);
				if (general->split.n_comand > 0 && general->commands[0][0] != '|')
					run_commands(&general);
				if (general->commands[0] && general->commands[0][0] == '|')
					printf(ERROR_PIPE);
				free_char_array2(general->commands);
			}
			free(general->line);
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
	general->cmd = NULL;
	general->split_line = NULL;
	general->exit_code = 0;


	general->env = copy_env(env);
	general->title = get_title(NULL);
	general->paths = get_env_paths(general->env);

	minishell(general);

	ft_clear_data(general);
    return (0);
}
