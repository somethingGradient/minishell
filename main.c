#include "minishell.h"

char	*mk_cmd(t_general *general, char *cmd)
{
	char	*temp;
	int		i;

	temp = cmd;
	i = -1;
	if (access(cmd, F_OK) > -1)
		return (cmd);
	general->paths = ft_split(getenv("PATH"), ':');
	while (general->paths[++i])
	{
		cmd = ft_strjoin(general->paths[i], temp);
		if (access(cmd, F_OK) > -1)
			return (cmd);
		free(cmd);
	}
	return (NULL);
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


int	execute_cmd(t_general *general)
{
	char	*temp;

	general->split_line = ft_split(general->line, ' ');
	if (!general->split_line)
		return (0);
	
	general->cmd = ft_strdup(general->split_line[0]);
	if (!general->cmd)
		return (0);

	if (!ft_strcmp(general->cmd, "echo"))
	{
		ft_echo(general);
		return 1;
	}
	if (!ft_strcmp(general->cmd, "cd"))
	{
		ft_cd(general);
		return 1;
	}
	// if (!ft_strcmp(general->cmd, "pwd"))
	// {
	// 	ft_pwd(general);
	// 	return 1;
	// }
	// 	if (!ft_strcmp(general->cmd, "env"))
	// {
	// 	// ft_env(general);
	// 	return 1;
	// }
	if (!ft_strcmp(general->cmd, "exit"))
		exit(EXIT_SUCCESS);
	


	int status;

	int flag = 0;
	int child = fork();

	char *cmd = general->cmd;
	if (child == 0)
	{
		if (access(cmd, F_OK) > -1)
		{
			if (execve(cmd, general->split_line, general->env) < 0)
			{
				printf("ERROR EXECVE.");
				exit(EXIT_FAILURE);
			}
		}
		int i = -1;
		while (general->paths[++i])
		{
			temp = cmd;
			cmd = ft_strjoin(general->paths[i], cmd);
			if (access(cmd, F_OK) > -1)
			{
				flag = 1;
				if ( execve(cmd, general->split_line, general->env) < 0)
				{
					printf("ERROR EXECVE.");
					exit(EXIT_FAILURE);
				}
			}
			cmd = temp;
		}
		if (!flag)
		{
			printf("Command '%s' not found.\n", cmd);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}

	waitpid(child, &status, 0);
	return (1);
}


void	sig_handler(int signal)
{
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}


void	minishell(t_general *general)
{
	char	*title;
	
	read_history("history");

	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("failed to register interrupts with kernel\n");

	while (1)
	{
		general->line = readline(general->title);
		if (general->line && *(general->line))
		{
			add_history(general->line);
			if (!pre_parser(general->line))
			{
				printf("%s\n", "EXIT! NOT CLOSED QUOTE.");
				continue ;
			}
			execute_cmd(general);
		}
		if (!general->line)
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		write_history("history");
		free(general->line);
	}
}

int	ft_exit(char *msg, int exit_code)
{
	if (msg)
		ft_putstr_fd(msg, 3);
	exit(exit_code);
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


	int i = -1;
	char *temp;
	while (general->paths[++i])
	{
		temp = general->paths[i];
		general->paths[i] = ft_strjoin(general->paths[i], "/");
		free(temp);
	}

	minishell(general);

	ft_clear_data(general);
    return (0);
}
