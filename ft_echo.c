
#include "minishell.h"

int	parse_backslash(char **str, int *i)
{
	if ((*str)[*i] != '\\')
		return (0);
	(*i)++;
	if (((*str)[*i] == '\\' || (*str)[*i] == '$')
		|| (*str)[*i] == '"')
		ft_putchar_fd((*str)[*i], 1);
	else
	{
		ft_putchar_fd('\\', 1);
		ft_putchar_fd((*str)[*i], 1);
	}
	(*i)++;
	return (1);
}

void	parse_env_and_bs(t_general *general, char **str, int *i)
{
	while (parse_backslash(str, i)
		|| print_env_var(general, str, i))
		parse_env_and_bs(general, str, i);
}

void	write_double_quotes(t_general *general, char **str, int *i)
{
	while ((*str)[++(*i)])
	{
		parse_env_and_bs(general, str, i);
		if ((*str)[*i] == '"' || !(*str)[*i])
			return ;
		ft_putchar_fd((*str)[*i], 1);
	}
}

int	str_trim(char *str, int n)
{
	int	i;

	i = 4;
	if (!n)
	{
		while (str[i] == ' ')
			i++;
	}
	else
	{
		while (str[i] == ' ')
			i++;
		while (ft_isprint(str[i]) && str[i] != ' ')
			i++;
		while (str[i] == ' ')
			i++;
	}
	i--;
	return (i);
}

int	main_echo(t_general *general, char *str, int n)
{
	int		i;

	i = str_trim(str, n);
	while (str[++i])
	{
		parse_env_and_bs(general, &str, &i);	
		if (!str[i])
			break ;
		else if (str[i] == '"')
			write_double_quotes(general, &(str), &i);
		else if (str[i] == '\'')
		{
			while (str[++i] && str[i] != '\'')
				ft_putchar_fd(str[i], 1);
		}
		else if (str[i] && ft_isprint(str[i]))
			ft_putchar_fd(str[i], 1);
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	return (0);
}

int check_n(char *str)
{

	if (!str)
		return (0);
	if (!ft_strcmp(str, "-n"))
		return (2);
	if (ft_strlen(str) != 4)
		return (0);
	if ((str[0] == '\'' && str[1] == '-' && str[2] == 'n')
		|| (str[0] == '\"' && str[1] == '-' && str[2] == 'n'))
		return (4);
	else
		return (0);
}

int	ft_echo(t_general *general)
{
	char	*temp;
	char	*str;

	str = ft_strdup(general->line);
	if (!str)
		return (-1);
	temp = str;
	while (*str == ' ')
		str++;
	main_echo(general, str, check_n(general->split_line[1]));
	free(temp);
	return (0);
}