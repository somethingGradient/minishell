/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:55:14 by akitty            #+#    #+#             */
/*   Updated: 2022/05/28 12:23:10 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pre_parser_main(char *str)
{
	t_flags	*flags;
	int		result;

	flags = NULL;
	flags = (t_flags *)malloc(sizeof(*flags));
	if (!flags)
		return (-1);
	flags->braces = 0;
	flags->backslash = 0;
	flags->single_quotes = 0;
	flags->dobles_quotes = 0;
	pre_parser(str, flags);
	if (flags->dobles_quotes || flags->single_quotes
		|| flags->braces || flags->backslash)
		result = -1;
	else
		result = 0;
	free(flags);
	return (result);
}
