#include "minishell.h"

// файл записывает в переменную general->out_fd дескриптор файла, если встречается '>'
// возвращает -1 в случае ошибки

int	redirect_out(t_general *general, int j)
{
	int		flags;
	char	*file;

	flags = O_WRONLY | O_CREAT;
	if (general->commands[j] && general->commands[j][0] == '>')
	{
		if (general->commands[j] && general->commands[j][1] == '>')
		{
			file = ft_strtrim(&general->commands[j][2], " ");
			if (!file)
				return (-1);
			general->out_fd = open(file, flags | O_APPEND, 744);
			free (file);
		}
		else
			simple_redir_out(general, j, flags);
		if (general->out_fd < 0)
			return (-1);
		general->last_redir = 1;
		if (general->split.n_comand == 1)
			free(general->line);
	}
}

// редирект >
int	simple_redir_out(t_general *general, int j, int flags)
{
	char	*aux;
	char	*file;

	aux = ft_strtrim(&general->commands[j][1], " ");
	file = ft_substr(aux, 0, find_char(aux, ' '));
	if (!file || !aux)
		general->out_fd = -1;
	general->out_fd = open(file, flags | O_TRUNC, 744);
	free (aux);
	free (file);
}

// находит символ needle в string и возвращает его индекс
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
