/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:57:39 by jannabel          #+#    #+#             */
/*   Updated: 2022/06/05 15:47:33 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_contain_name(char *name, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name))
			&& env[i][ft_strlen(name)] == '=')
			return (1);
	}
	return (0);
}

int	is_env_contain_var(char *var, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strcmp(env[i], var))
			return (1);
	}
	return (0);
}

static void	fix_for_norm2(char *var, int ind, char **name, t_general *general)
{
	char	*srcval;
	char	*joinval;
	char	*newval;

	srcval = ft_get_env_value(general->env, var);
	joinval = ft_substr(name[1], ind, ft_strlen(name[1]));
	newval = ft_strjoin(srcval, joinval);
	free(srcval);
	free(joinval);
	change_env(general, name[0], newval);
	free(newval);
}

void	check_name_utils(char **name, t_general *general)
{
	int		ind;
	char	*keyinvar;	
	char	*value;

	ind = -1;
	while (name[1][++ind])
	{
		if (name[1][ind] == ':' || name[1][ind] == '/')
			break ;
	}
	keyinvar = ft_substr(name[1], 1, ind - 1);
	if (is_env_contain_name(keyinvar, general->env))
		fix_for_norm2(keyinvar, ind, name, general);
	else
	{
		value = ft_substr(name[1], ft_strlen(keyinvar) + 1, ft_strlen(name[1]));
		change_env(general, name[0], value);
		free(value);
	}
	free(keyinvar);
}
