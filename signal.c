/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:08:02 by akitty            #+#    #+#             */
/*   Updated: 2022/06/04 13:08:04 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_code = 130;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_backslash(int signal)
{
	if (signal == SIGQUIT)
	{
		g_exit_code = 131;
		printf("Quit (core dumped)\n");
		(void)signal;
	}
}

void	sig_handler(t_general *general, int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_backslash);
	}
	else if (mode == 3)
	{
		printf("exit\n");
		ft_clear_data(general);
		exit(0);
	}
}
