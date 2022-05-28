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

static void	ft_clear_data(t_general *general)
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

static void	sig_handler(int signal)
{
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

static int	minishell(t_general *general)
{
	general->line = ft_strdup("export");

	// read_history("history");
	// if (signal(SIGINT, sig_handler) == SIG_ERR)
	// 	printf("failed to register interrupts with kernel\n");
	// while (1337)
	// {
	// 	general->line = readline(general->title);
	// 	general->line[ft_strlen(general->line)] = '\0';
		if (general->line && *(general->line))
		{
			add_history(general->line);
			if (pre_parser_main(general->line) != 0)
			{
				ft_putstr_fd("Error.\nLine is a not closed.\n", 2);
				// continue ;
			}
			else
			{
				split_cmd(general, general->line, 0);
				run_commands(general);
			}
	// 		write_history("history");
		}
	// }
	return (0);
}

static t_general	*init_general(t_general *general, char **env)
{
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
		ft_putstr_fd("Error in setupping variables.\n", 2);
		exit(EXIT_FAILURE);
	}
	return (general);
}

int	main(int argc, char **argv, char **env)
{
	t_general	*general;

	general = init_general(general, env);
	minishell(general);
	ft_clear_data(general);
	exit(EXIT_SUCCESS);
}
