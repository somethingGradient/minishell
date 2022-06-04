/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:57:39 by jannabel          #+#    #+#             */
/*   Updated: 2022/06/04 19:57:43 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_env_contain_name(char *name, char **env)
{
	int i;
	
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name))
		&& env[i][ft_strlen(name)] == '=')
			return (1);
	}
	return (0);
}

int is_env_contain_var(char *var, char **env)
{
	int i;
	
	i = -1;
	while (env[++i])
	{
		if (!ft_strcmp(env[i], var))
			return (1);
	}
	return (0);
}
