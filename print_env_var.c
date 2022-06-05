/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:36:06 by jannabel          #+#    #+#             */
/*   Updated: 2022/05/28 12:37:21 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dollar(char **str, int *i, int out_fd)
{
	if ((*str)[*i] == '$')
	{
		(*i)++;
		if (!ft_isalpha((*str)[*i]) && (*str)[*i] != '?')
		{
			ft_putchar_fd('$', out_fd);
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

int	print_env_var(t_general *general, char *str, int *i, char *buf)
{
	char	*temp;

	if (!check_dollar(&str, i, general->out_fd))
		return (0);
	if (ft_isalnum(str[*i]))
	{
		buf = ft_calloc(sizeof(char), 512);
		if (!buf)
			return (-1);
		buf_env(&str, i, &buf);
		temp = ft_get_env_value(general->env, buf);
		free(buf);
		if (temp)
		{
			ft_putstr_fd(temp, general->out_fd);
			free(temp);
		}
	}
	else if (str[*i] == '?')
	{
		ft_putnbr_fd(g_exit_code, general->out_fd);
		(*i)++;
	}
	print_env_var(general, str, i, NULL);
	return (1);
}
