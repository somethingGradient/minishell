#include "minishell.h"

void	split_cmd(t_general *general, char *in, int i)
{
	init_split_struct(general);
	in = clean_spaces(in);
	while (i < ft_strlen(in))
	{
		if (general->split.quote == 0 && (in[i] == D_QUOTE || in[i] == QUOTE))
			general->split.quote = in[i];
		else
		{
			if (general->split.quote == in[i])
				general->split.quote = 0;
			else
				i = count_pipe(general, in, i);
		}
		general->split.len++;
		i++;
	}
	if (ft_strlen(in) > 0)
	{
		general->commands[general->split.n_comand]
			= ft_substr(in, general->split.ini, i);
		general->split.n_comand++;
	}
	free(in);
	general->commands[general->split.n_comand] = NULL;
}

void	init_split_struct(t_general *general)
{
	general->split.n_comand = 0;
	general->split.ini = 0;
	general->split.len = 0;
	general->split.qtt_pipe = 0;
	general->split.quote = 0;
	general->last_redir = 0;
}

char	*clean_spaces(char *in)
{
	char	*aux;

	aux = ft_strtrim(in, " ");
	in = aux;
	return (in);
}

int	count_pipe(t_general *general, char *in, int i)
{
	if (in[i] == '|' || in[i] == '<' || in[i] == '>')
	{
		if (in[i] == '|' && general->split.quote == 0)
			general->split.qtt_pipe++;
		if (general->split.quote == 0 && i > 1 && general->split.len > 0)
		{
			general->commands[general->split.n_comand] = ft_substr(in,
					general->split.ini + 1, general->split.len);
			general->split.ini = i;
			general->split.len = 0;
			general->split.n_comand++;
			if (in[i] == '>')
				general->last_redir = 1;
			else
				general->last_redir = 0;
			if (in[i] == in[i + 1])
			{
				i++;
				general->split.len = 1;
			}
		}
	}
	return (i);
}