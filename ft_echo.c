
#include "minishell.h"

int	write_env_var(char **str, int *i)
{
	char	*buf;
	char	*temp;
	int		flag;
	int		k;

	(*i)++;
	k = -1;
	flag = 0;
	buf = ft_calloc(sizeof(char), 512);
	if ((*str)[*i] == '{')
	{
		flag = 1;
		(*i)++;
	}
	while ((*str)[*i] && ((ft_isalnum((*str)[*i]) || (*str)[*i] == '_')
		&& (*str)[*i] != ' '
		&& (*str)[*i] != '"'))
	{
		if (flag == 1)
		{
			if ((*str)[(*i)] == '}')
			{
				i++;
				break ;
			}
			buf[++k] = (*str)[(*i)++];
		}
		else
			buf[++k] = (*str)[(*i)++];
	}
	if (flag)
		(*i)++;
	buf[k + 1] = '\0';
	temp = getenv(buf);
	free(buf);
	if (!temp)
	{
		if ((*str)[*i] != '"') 
			(*i)--;
		return (0) ;
	}
	ft_putstr_fd(temp, 1);
	return (1);
}

int	parse_backslash(char **str, int *i)
{
	if ((*str)[*i] == '\\')
	{
		if ((*str)[(*i) + 1] == '\\')
		{
			ft_putchar_fd('\\', 1);
			(*i) += 2;
		}
		else if ((*str)[(*i) + 1] == '$')
		{
			ft_putchar_fd('$', 1);
			(*i) += 2;
		}
		else if ((*str)[(*i) + 1] == '"')
		{
			ft_putchar_fd('"', 1);
			(*i) += 2;
		}
		else
		{
			ft_putchar_fd((*str)[*i], 1);
			(*i)++;
		}
		if (!((*str))[*i])
			return (0);
	}
	return (1);
}

void	write_double_quotes(char **str, int *i)
{
	while ((*str)[++(*i)] && (*str)[*i] != '"')
	{
		if (!parse_backslash(str, i))
			return ;
		if ((*str)[(*i)] == '$' && (ft_isalnum((*str)[(*i) + 1]) || (*str)[(*i) + 1] == '{'))
		{
			if (write_env_var(str, i) == 0)
				continue ;
		}
		if ((*str)[(*i)] == '$' && (ft_isalnum((*str)[(*i) + 1]) || (*str)[(*i) + 1] == '{'))
		{
			(*i) -= 1;
			continue ;
		}
		if ((*str)[(*i)] && (*str)[(*i) + 1] && (*str)[(*i) + 1] == '"')
		{
			ft_putchar_fd((*str)[(*i)++], 1);
			continue;
		}
		if ((*str)[(*i)] && (*str)[(*i)] != '"' && (*str)[(*i)] != '}')
			ft_putchar_fd((*str)[(*i)], 1);
	}
}

int	main_echo(t_general *general, int n)
{
	int		i;

	if (!n)
		i = 4;
	else
		i = n;
	while (general->line[++i])
	{
		if (general->line[i] == '"')
			write_double_quotes(&(general->line), &i);
		if (general->line[i] == '\'')
		{
			while (general->line[++i] && general->line[i] != '\'')
				ft_putchar_fd(general->line[i], 1);
		}
		if (general->line[i] && ft_isprint(general->line[i]))
			ft_putchar_fd(general->line[i], 1);
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	return (0);
}

int check_n(char *str)
{
	if (!ft_strcmp(str, "-n"))
		return (7);
	if (ft_strlen(str) != 4)
		return (0);
	if (str[0] == '\'' && str[1] == '-' && str[2] == 'n')
		return (9);
	else if (str[0] == '\"' && str[1] == '-' && str[2] == 'n')
		return (9);
	else
		return (0);
}

int	ft_echo(t_general *general)
{
	int i;
	int flag;

	i = -1;
	flag = 1;
	general->line[ft_strlen(general->line) + 1] = '\0';
	main_echo(general, check_n(general->split_line[1]));
	return (1);
}