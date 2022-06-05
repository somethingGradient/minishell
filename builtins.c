/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:11:28 by jannabel          #+#    #+#             */
/*   Updated: 2022/05/28 16:00:04 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit(t_general *general)
{
	int	i;

	i = -1;
	printf("exit\n");
	while (general->token.to_print[++i])
	{
		if (!ft_isdigit(general->token.to_print[i]))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				general->token.to_print);
			exit(255);
		}
	}
	g_exit_code = ft_atoi(general->token.to_print) % 256;
	free_char_array(general->tokens);
	free_char_array(general->commands);
	free(general->token.to_print);
	free(general->token.to_exec);
	if (general->line)
	{
		free(general->line);
		general->line = NULL;
	}
	ft_clear_data(general);
	exit(g_exit_code);
}

void	is_builtin(char *cmd, t_general *general)
{
	if ((!ft_strncmp("echo", cmd, 4) && ft_strlen(cmd) == 4)
		|| (!ft_strncmp("cd", cmd, 2) && ft_strlen(cmd) == 2)
		|| (!ft_strncmp("pwd", cmd, 3) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp("export", cmd, 6) && ft_strlen(cmd) == 6)
		|| (!ft_strncmp("unset", cmd, 5) && ft_strlen(cmd) == 5)
		|| (!ft_strncmp("env", cmd, 3) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp("exit", cmd, 4) && ft_strlen(cmd) == 4))
		general->is_builtin = TRUE;
	else
		general->is_builtin = FALSE;
}

void	run_builtin(t_general *general)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (!ft_strncmp(general->tokens[0], "exit", 4))
		ft_exit(general);
	if (!ft_strncmp(general->tokens[0], "pwd", 3))
		ft_pwd(general);
	if (!ft_strncmp(general->tokens[0], "echo", 4))
		ft_echo(general);
	if (!ft_strncmp(general->tokens[0], "cd", 2))
		ft_cd(general);
	if (!ft_strncmp(general->tokens[0], "env", 3))
		ft_show_env(general->env, general->out_fd);
	if (!ft_strncmp(general->tokens[0], "export", 6))
		ft_export(general);
	if (!ft_strncmp(general->tokens[0], "unset", 5))
		ft_unset(general);
}
