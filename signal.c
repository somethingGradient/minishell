#include "minishell.h"


void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_ret_number = 130;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_c(int signal)
{
	g_ret_number = 130;
	write(1, "\n", 1);
	(void)signal;
}

void	back_slash(int signal)
{
	g_ret_number = 131;
	printf("Quit (core dumped)\n");
	(void)signal;
}
