/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:40:58 by jannabel          #+#    #+#             */
/*   Updated: 2022/06/04 13:08:42 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*new_comman(int i, char **str)
{
	char	*aux;

	aux = ft_strdup("");
	while (str[i] != NULL)
	{
		if (ft_strlen(aux) > 0)
			aux = ft_strjoin(aux, " ");
		aux = ft_strjoin(aux, str[i]);
		i++;
	}
	return (aux);
}

static void	read_until(char *end)
{
	char	*line;
	int		flags;
	int		fd;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	line = ft_strdup("");
	fd = open(end, flags, 0777);
	while (ft_strncmp(line, end, ft_strlen(end))
		|| ft_strlen(line) != ft_strlen(end))
	{
		free(line);
		line = readline("> ");
		if (ft_strlen(line) != ft_strlen(end))
			ft_putendl_fd(line, fd);
	}
	close(fd);
	free(line);
}

static char	**double_redir(t_general *general, char **file, int j)
{
	file = ft_split(&general->commands[j][2], ' ');
	if (!file)
		return (NULL);
	read_until(file[0]);
	general->in_fd = open(file[0], O_RDONLY | O_CREAT, 0777);
	general->name_file = ft_strdup(file[0]);
	general->is_append++;
	return (file);
}

static int	for_norm(t_general *general, char **file, int j)
{
	file = ft_split(&general->commands[j][1], ' ');
	if (!file)
		return (FALSE);
	general->in_fd = open(file[0], O_RDONLY, 0777);
	if (general->in_fd == -1 && general->error_name_file == NULL)
	{
		general->error_name_file = ft_strdup(file[0]);
		if (!general->error_name_file)
			return (FALSE);
	}
	return (TRUE);
}

int	redirect_in(t_general *general, int j, char *aux)
{
	char	**file;

	if (general->commands[j][0] == '<')
	{
		file = NULL;
		if (general->commands[j][1] == '<')
			file = double_redir(general, file, j);
		else
		{
			if (!for_norm(general, file, j))
				return (-1);
		}
		aux = ft_strtrim(general->line, " ");
		if (general->split.n_comand == 1 || (aux[0] == '|'
				&& ft_strlen(aux) == 1))
		{
			free(general->line);
			general->line = new_comman(1, file);
		}
		free(aux);
		general->last_redir = 0;
		free_char_array(file);
	}
	return (0);
}
