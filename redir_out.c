#include "minishell.h"

void	redirect_out(t_general *general, int j)
{
	int		flags;
	char	*file;

	flags = O_WRONLY | O_CREAT;
	j = general->c;
	if (general->commands[j] && general->commands[j][0] == '>')
	{
		if (general->commands[j] && general->commands[j][1] == '>')
		{
			file = ft_strtrim(&general->commands[j][2], " ");
			general->out_fd = open(file, flags | O_APPEND, 0777);
			free (file);
		}
		else
			simple_redir_out(general, j, flags);
		general->last_redir = 1;
		if (general->split.n_comand == 1)
			free(general->line);
	}
}

void	simple_redir_out(t_general *general, int j, int flags)
{
	char	*aux;
	char	*file;

	aux = ft_strtrim(&general->commands[j][1], " ");
	file = ft_substr(aux, 0, find_char(aux, ' '));
	general->out_fd = open(file, flags | O_TRUNC, 0777);
	free (aux);
	free (file);
}

int	find_char(char *string, char needle)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == needle)
			return (i);
		i++;
	}
	return (i);
}
