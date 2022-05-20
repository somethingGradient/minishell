#include "minishell.h"

char	*mk_cmd_token(t_general *general, char *cmd)
{
	char	*temp;
	int		i;
	char	c;

	i = -1;
	if (!cmd || !ft_strlen(cmd))
		return (cmd);
	if (access(cmd, F_OK) > -1)
		return (cmd);
	general->paths = get_env_paths(general->env);
	while (general->paths[++i])
	{
		temp = cmd;
		cmd = ft_strjoin(general->paths[i], cmd);
		if (access(cmd, F_OK) > -1)
		{
			free(temp);
			return (cmd);
		}
		free(cmd);
		cmd = temp;
	}
	return (NULL);
}

void	run_commands(t_general *general)
{
	int		j;
	int		fd[2];

	j = 0;
	general->index_cmd = 0;
	general->last_redir = 0;
	while (j < general->split.qtt_pipe)
	{
		if (pipe(fd) < 0)
		{
			printf("Pipe error\n");
			g_ret_number = 127;
		}
		general->out_fd = fd[1];
		run_commands_aux(general);
		close(general->out_fd);
		if (general->in_fd != 0)
			close(general->in_fd);
		general->in_fd = fd[0];
		j++;
	}
	run_commands_aux(general);
}

void	run_commands_aux(t_general *general)
{
	action(general);
	if (general->commands[0][0] != '>')
	{
		tokenizer(general);



		if (general->tokens[0])
			is_builtin(general->tokens[0], general);
		if (general->in_fd != -1)
			exec_process(general, general->in_fd, general->out_fd);
		free_char_array(general->tokens);
		free(general->token.to_print);
		free(general->token.to_exec);
	}
	if (general->name_file)
		unlink(general->name_file);
}

void	action(t_general *general)
{
	general->line = ft_strdup(general->commands[general->index_cmd]);
	if (general->split.n_comand > 1)
		general->index_cmd++;
	general->error_name_file = NULL;
	while (general->commands[general->index_cmd]
			&& general->commands[general->index_cmd][0] != '|')
	{
		redirect_out(general, general->index_cmd);
		redirect_in(general, general->index_cmd, NULL);
		general->index_cmd++;
	}
	if (general->error_name_file != NULL)
	{
		g_ret_number = 1;
		printf("minishell: %s: %s", general->error_name_file, ERROR_DIR);
		free(general->error_name_file);
	}
}

void	exec_process(t_general *general, int in, int out)
{
	pid_t	pid;

	if (general->is_builtin && general->tokens[0])
		run_builtin(general);
	else
	{
		pid = fork();
		if (pid < 0)
		{
			printf("Fork error\n");
			g_ret_number = 127;
		}
		else if (pid == 0)
		{
			file_descriptor_handler(in, out);
			g_ret_number = 127;
			ft_execve_pipe(general, 0, "");
			exit(g_ret_number);
		}
		else
			waitpid(pid, &g_ret_number, WUNTRACED);
		if (WIFEXITED(g_ret_number))
			g_ret_number = WEXITSTATUS(g_ret_number);
	}
}

void	ft_execve_pipe(t_general *general, int i, char *command)
{
	if (general->tokens[0])
	{
		// general->tokens[0] = mk_cmd_token(general, general->tokens[0]); // added
		g_ret_number = execve(general->tokens[0], &general->tokens[0], general->env);
		while (general->paths && general->paths[i] != NULL)
		{
			command = ft_strdup(general->paths[i]);
			if (general->tokens[0][0] == '|' && general->tokens[1])
			{
				if (!general->tokens[0][1])
					spaces_in_pipe(general, 2, command);
				else
				{
					general->tokens[0] = &general->tokens[0][1];
					spaces_in_pipe(general, 1, command);
				}
			}
			else
				spaces_in_pipe(general, 1, command);
			i++;
		}
		execve_error(general);
	}
}
