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
