/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:24:42 by jannabel          #+#    #+#             */
/*   Updated: 2022/05/28 14:26:38 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_backslash(char *str, int *i, int out_fd)
{
	if (str[*i] != '\\')
		return (0);
	(*i)++;
	if ((str[*i] == '\\' || str[*i] == '$')
		|| str[*i] == '"')
		ft_putchar_fd(str[*i], out_fd);
	else
		ft_putchar_fd(str[*i], out_fd);
	(*i)++;
	return (1);
}

void	parse_env_and_bs(t_general *general, char *str, int *i)
{
	while (parse_backslash(str, i, general->out_fd)
		|| print_env_var(general, str, i, NULL))
		parse_env_and_bs(general, str, i);
}

int	ft_echo(t_general *general)
{
	int		i;

	i = -1;
	while (general->token.to_print[++i]
		&& i <= ft_strlen(general->token.to_print))
	{
		parse_env_and_bs(general, general->token.to_print, &i);
		if (general->token.to_print[i]
			&& ft_isprint(general->token.to_print[i]))
			ft_putchar_fd(general->token.to_print[i], general->out_fd);
	}
	if (!general->has_flag)
		ft_putchar_fd('\n', general->out_fd);
	g_exit_code = 0;
	return (0);
}
