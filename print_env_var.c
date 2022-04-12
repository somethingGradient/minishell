
#include "minishell.h"

int	check_dollar(char **str, int *i)
{
	if ((*str)[*i] == '$')
	{
		(*i)++;
		if (!ft_isalpha((*str)[*i]) && (*str)[*i] != '?')
		{
			ft_putchar_fd('$', 1);
			return (0);	
		}
	}
	else
		return (0);
	return (1);
}

void	buf_env(char **str, int *i, char **buf)
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

int	print_env_var(t_general *general, char **str, int *i)
{
	char	*buf;
	char	*temp;

	if (!check_dollar(str, i))
		return (0);
	if (ft_isalnum((*str)[*i]))
	{
		buf = ft_calloc(sizeof(char), 512);
		if (!buf)
			return (-1);
		buf_env(str, i, &buf);
		temp = ft_get_env(general->env, buf);
		free(buf);
		if (temp)
		{
			ft_putstr_fd(temp, 1);
			free(temp);
		}
	}
	else if ((*str)[*i] == '?')
	{
		ft_putnbr_fd(general->exit_code, 1);
		(*i)++;
	}
	print_env_var(general, str, i);
	return (1);
}