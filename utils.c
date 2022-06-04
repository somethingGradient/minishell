/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:28:10 by jannabel          #+#    #+#             */
/*   Updated: 2022/05/28 14:28:25 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_char_array(char **array)
{
	int	i;

	i = -1;
	if (array)
	{
		while (array[++i] != NULL)
		{
			free(array[i]);
			array[i] = NULL;
		}
	}
	else
		return ;
	free(array);
	array = NULL;
}

void	ft_clear_data(t_general *general)
{
	if (general)
	{
		free_char_array(general->env);
		free_char_array(general->paths);
		if (general->title)
			free(general->title);
		if (general->line)
			free(general->line);
		if (general->home)
			free(general->home);
		general->home = NULL;
		general->line = NULL;
		general->title = NULL;
		free(general);
		general = NULL;
	}
}
