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

typedef struct s_flags
{
	int	dobles_quotes;
	int	single_quotes;
	int	braces;
	int	backslash;
}	t_flags;

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

/* return 1 if line unclosed */
int	pre_parser(char *str)
{
	t_flags	*flags;
	int		i;

	flags = NULL;
	flags = (t_flags *)malloc(sizeof(*flags));
	flags->dobles_quotes = 0;
	flags->single_quotes = 0;
	flags->braces = 0;
	flags->backslash = 0;
	i = -1;
	while (str[++i])
	{
		pre_parser_backslash(&str, &i, flags);
		if (str[i] == '\'')
			pre_parser_single_quotes(&str, &i, flags);
		else if (str[i] == '"') 
			pre_parser_double_quotes(&str, &i, flags);
	}
	if (flags->dobles_quotes || flags->single_quotes
		|| flags->braces || flags->backslash)
		i = 1;
	else
		i = 0;
	free(flags);
	return (i);
}
