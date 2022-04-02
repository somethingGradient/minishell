
#include "minishell.h"

int	check_dollar(char **str, int *i)
{
	if ((*str)[*i] == '$')
	{
		(*i)++;
		if ((*str)[*i] == '?')
			// WRITE EXIT CODE
		if (!ft_isprint((*str)[*i]))
		{
			ft_putchar_fd('$', 1);
			return (0);	
		}
	}
	else
		return (0);
	return (1);
}

char	buf_env(char **str, int *i, char **buf)
{
	int		flag;
	int		k;

	flag = 0;
	k = -1;
	if ((*str)[*i] == '{')
	{
		flag = 1;
		(*i)++;
	}
	while ((*str)[*i] && ((ft_isalnum((*str)[*i]) || (*str)[*i] == '_')
		&& (*str)[*i] != ' ' && (*str)[*i] != '"'))
	{
		if (flag == 1)
		{
			if ((*str)[(*i)] == '}')	
				break ;
			(*buf)[++k] = (*str)[(*i)++];
		}
		else
			(*buf)[++k] = (*str)[(*i)++];
	}
	if (flag)
		(*i)++;
	(*buf)[k + 1] = '\0';
}

int	write_env_var(char **str, int *i)
{
	char	*buf;
	char	*temp;

	if (!check_dollar(str, i))
		return (0);
	buf = ft_calloc(sizeof(char), 512);
	if (!buf)
		return (-1);
	buf_env(str, i, &buf);
	temp = getenv(buf);
	free(buf);
	ft_putstr_fd(temp, 1);
	write_env_var(str, i);
	return (1);
}