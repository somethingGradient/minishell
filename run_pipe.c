/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:29:01 by jannabel          #+#    #+#             */
/*   Updated: 2022/05/28 15:20:23 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execve_pipe(t_general *general, int i, char *command)
{
	if (general->tokens[0])
	{
		expr_utils(general, 0);
		free_char_array(general->paths);
		general->paths = get_env_paths(general->env);
		g_exit_code = execve(general->tokens[0],
				general->tokens, general->env);
		while (general->paths && general->paths[++i] != NULL)
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
		}
		execve_error(general);
	}
}

static void	exec_process(t_general *general, int in, int out)
{
	pid_t	pid;

	if (general->is_builtin && general->tokens[0])
		run_builtin(general);
	else
	{
		pid = fork();
		sig_handler(general, 2);
		if (pid < 0)
		{
			printf("Fork error\n");
			g_exit_code = 127;
		}
		else if (pid == 0)
		{
			file_descriptor_handler(in, out);
			ft_execve_pipe(general, -1, "");
			exit(g_exit_code);
		}
		else
			waitpid(pid, &g_exit_code, WUNTRACED);
		if (WIFEXITED(g_exit_code))
			g_exit_code = WEXITSTATUS(g_exit_code);
	}
}

static void	action(t_general *general)
{
	char	*temp;

	temp = general->line;
	general->line = ft_strdup(general->commands[general->index_cmd]);
	free(temp);
	temp = NULL;
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
		g_exit_code = 1;
		printf("minishell: %s: %s", general->error_name_file, ERROR_DIR);
		free(general->error_name_file);
	}
}

static void	run_commands_aux(t_general *general)
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

void	run_commands(t_general *general)
{
	int	j;
	int	fd[2];

	j = 0;
	general->index_cmd = 0;
	general->last_redir = 0;
	while (j < general->split.qtt_pipe)
	{
		if (pipe(fd) < 0)
		{
			printf("Pipe error\n");
			g_exit_code = 127;
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
