/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:25:32 by jannabel          #+#    #+#             */
/*   Updated: 2022/05/28 12:25:41 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pre_parser_single_quotes(char **str, int *i, t_flags *flags)
{
	flags->single_quotes = 1;
	while ((*str)[++(*i)])
	{
		if ((*str)[*i] == '\'')
		{
			flags->single_quotes = 0;
			return ;
		}
	}
}

void	pre_parser_dollar_quotes(char **str, int *i, t_flags *flags)
{
	if ((*str)[*i] == '$')
	{
		(*i)++;
		if ((*str)[*i] == '{')
		{
			flags->braces = 1;
			while ((*str)[++(*i)])
			{
				if (!ft_isalnum((*str)[*i]) && (*str)[*i] != '}')
					return ;
				if ((*str)[*i] == '}')
				{
					(*i)++;
					flags->braces = 0;
					return ;
				}
			}
		}
	}
}

void	pre_parser_backslash(char **str, int *i, t_flags *flags)
{
	if ((*str)[*i] == '\\')
	{
		flags->backslash = 1;
		(*i)++;
		if (ft_isprint((*str)[*i]))
		{
			(*i)++;
			flags->backslash = 0;
		}
		pre_parser_backslash(str, i, flags);
	}
}

void	pre_parser_double_quotes(char **str, int *i, t_flags *flags)
{
	flags->dobles_quotes = 1;
	while ((*str)[++(*i)])
	{
		pre_parser_backslash(str, i, flags);
		pre_parser_dollar_quotes(str, i, flags);
		if ((*str)[*i] == '"')
		{
			flags->dobles_quotes = 0;
			return ;
		}
	}
}

void	pre_parser(char *str, t_flags *flags)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		pre_parser_backslash(&str, &i, flags);
		if (str[i] == '\'')
			pre_parser_single_quotes(&str, &i, flags);
		else if (str[i] == '"')
		{
			flags->dobles_quotes = 1;
			while (str[++i])
			{
				pre_parser_backslash(&str, &i, flags);
				pre_parser_dollar_quotes(&str, &i, flags);
				if (str[i] == '"')
				{
					flags->dobles_quotes = 0;
					return ;
				}
			}
		}
	}
}
