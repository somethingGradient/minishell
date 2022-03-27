/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:55:14 by akitty            #+#    #+#             */
/*   Updated: 2022/03/26 17:55:16 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pre_parser_single_quotes(char **str, int *i, int *flag)
{
	while ((*str)[++(*i)])
	{
		if ((*str)[*i] == '\'')
		{
			*flag = 1;
			return ;
		}
	}
}

int	pre_parser_dollar_quotes(char **str, int *i, int *flag)
{
	if ((*str)[*i] == '$')
	{
		if (((*str)[(*i) + 1]) == '{')
		{
			*flag = 0;
			while ((*str)[++(*i)])
			{
				if ((*str)[*i] == '}')
				{
					(*i)++;
					*flag = 1;
					break ;
				}
			}
		}
	}
	if (*flag == 1)
		return (1);
	else
		return (0);
}

void	pre_parser_double_quotes(char **str, int *i, int *flag)
{
	while ((*str)[++(*i)])
	{
		if ((*str)[*i] == '\\' && (*str)[(*i) + 1] == '\\')
		{
			*i += 2;
			if ((*str)[*i] && (*str)[(*i) + 1]
				&& (*str)[*i] == '\\' && (*str)[(*i) + 1] == '\\')
				i += 2;
			if (!(*str)[*i] || (*str)[*i] == '"'
				|| ((*str)[*i] != ' ' && !ft_isprint((*str)[*i])))
			{
				*flag = 1;
				return ;
			}
		}
		if (((*str)[*i] == '"' && (!((*str)[(*i) + 1])
			|| ((*str)[(*i) + 1]) == ' ') && ((*str)[(*i) - 1]) != '\\')
			|| ((*str)[*i] == '"' && *flag != 1 && (*str)[(*i) - 1] != '\\'))
		{
			*flag = 1;
			return ;
		}
		if (pre_parser_dollar_quotes(str, i, flag))
			continue ;
	}
}

int	pre_parser(char *str)
{
	int	i;
	int	flag;
	int	counter;

	i = -1;
	counter = 0;
	flag = 1;
	while (str[++i])
	{
		if (str[i] == '\\' && !str[i + 1])
			return (0);
		else if (str[i] == '\'' && str[i - 1] != '\\')
		{
			flag = 0;
			pre_parser_single_quotes(&str, &i, &flag);
		}
		else if (str[i] == '"' && str[i - 1] != '\\' )
		{
			flag = 0;
			pre_parser_double_quotes(&str, &i, &flag);
		}
	}
	if (!flag)
		return (0);
	return (1);
}
