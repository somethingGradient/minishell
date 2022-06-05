/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:43:46 by jannabel          #+#    #+#             */
/*   Updated: 2022/05/28 14:23:49 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sh_kernel(t_general *general)
{
	if (*(general->line))
	{
		general->line[ft_strlen(general->line)] = '\0';
		add_history(general->line);
		if (pre_parser_main(general->line) != 0)
		{
			ft_putstr_fd("Error.\nLine is a not closed.\n", 2);
			g_exit_code = -1;
			return (-1);
		}
		split_cmd(general, general->line, 0);
		if (general->split.n_comand > 0 && general->commands[0][0] != '|')
			run_commands(general);
		if (general->commands[0] && general->commands[0][0] == '|')
			printf(ERROR_PIPE);
		free(general->line);
		general->line = NULL;
		free_char_array(general->commands);
		write_history("history");
	}
	return (0);
}

static int	minishell(t_general *general)
{
	read_history("history");
	while (1337)
	{
		general->out_fd = STDOUT_FILENO;
		general->in_fd = STDIN_FILENO;
		sig_handler(general, 1);
		general->line = readline(general->title);
		if (general->line)
		{
			if (sh_kernel(general) == -1)
				continue ;
			continue ;
		}
		else
			sig_handler(general, 3);
	}
	return (0);
}

static void	change_shlvl(t_general *general)
{
	int		i;
	char	*current;
	char	*temp;

	temp = NULL;
	current = NULL;
	temp = ft_get_env_value(general->env, "SHLVL");
	current = ft_itoa(ft_atoi(temp) + 1);
	free(temp);
	temp = ft_strjoin("SHLVL=", current);
	free(current);
	i = -1;
	while (general->env[++i])
	{
		if (ft_strnstr(general->env[i], "SHLVL=", 6))
		{
			current = general->env[i];
			break ;
		}
	}
	free(general->env[i]);
	general->env[i] = temp;
	current = NULL;
	temp = NULL;
}

static t_general	*init_general(t_general *general, char **env)
{
	general = (t_general *)malloc(sizeof(*general));
	general->paths = NULL;
	general->env = NULL;
	general->title = NULL;
	general->line = NULL;
	general->home = NULL;
	general->commands = NULL;
	general->tokens = NULL;
	general->name_file = NULL;
	general->error_name_file = NULL;
	general->paths = NULL;
	general->env = copy_env(env);
	general->home = ft_get_env_value(general->env, "HOME");
	get_title(general, NULL);
	change_shlvl(general);
	if (!general || !general->env || !general->title)
	{
		ft_clear_data(general);
		ft_putstr_fd("Error in setupping variables.\n", 2);
		exit(EXIT_FAILURE);
	}
	return (general);
}

int	main(int argc, char **argv, char **env)
{
	t_general	*general;

	argc = 0;
	argv = NULL;
	general = NULL;
	general = init_general(general, env);
	minishell(general);
	ft_clear_data(general);
	return (0);
}
