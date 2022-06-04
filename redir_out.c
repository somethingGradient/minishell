/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:41:06 by jannabel          #+#    #+#             */
/*   Updated: 2022/06/04 13:07:17 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_char(char *string, char needle)
{
	int	i;

	i = -1;
	while (string[++i])
	{
		if (string[i] == needle)
			return (i);
	}
	return (i);
}

static void	simple_redir_out(t_general *general, int j, int flags)
{
	char	*aux;
	char	*file;

	aux = ft_strtrim(&general->commands[j][1], " ");
	file = ft_substr(aux, 0, find_char(aux, ' '));
	general->out_fd = open(file, flags | O_TRUNC, 0777);
	free (aux);
	free (file);
}

static void	for_norm(t_general *general)
{
	free(general->line);
	general->line = NULL;
}

int	redirect_out(t_general *general, int j)
{
	int		flags;
	char	*file;

	flags = O_WRONLY | O_CREAT;
	if (general->commands[j] && general->commands[j][0] == '>')
	{
		if (general->commands[j] && general->commands[j][1] == '>')
		{
			file = ft_strtrim(&general->commands[j][2], " ");
			if (!file)
				return (-1);
			general->out_fd = open(file, flags | O_APPEND, 0777);
			free (file);
		}
		else
			simple_redir_out(general, j, flags);
		general->last_redir = 1;
		if (general->split.n_comand == 1)
			for_norm(general);
		if (general->out_fd < 0)
			return (-1);
	}
	return (0);
}
