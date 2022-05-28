/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:58:39 by jannabel          #+#    #+#             */
/*   Updated: 2022/05/28 11:22:35 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_general *general)
{
	int		i;
	char	**envname;

	if (ft_strlen(general->token.to_print))
	{
		i = 0;
		while (general->env[i])
		{
			envname = ft_split(general->env[i], '=');
			if (!ft_strcmp(general->token.to_print, envname[0]))
			{
				general->env[i] = "\0";
				break ;
			}
			i++;
		}
		return ;
	}
	else
		ft_putstr_fd("unset: not enough arguments\n", 1);
}
