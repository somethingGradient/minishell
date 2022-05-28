#include "minishell.h"

static void	ctrl_c(int sig)
{
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	(void)sig;
}

void	run_signals()
{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, SIG_IGN);
}