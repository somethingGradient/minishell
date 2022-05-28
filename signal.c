#include "minishell.h"

void	ft_sighandler(int sig)
{
	if (sig == SIGINT)
	{
		//g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}