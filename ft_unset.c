/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:58:39 by jannabel          #+#    #+#             */
/*   Updated: 2022/06/05 16:41:15 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_newenv(char **newenv, char **env, char *var)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (env[++i])
	{
		if (!strncmp(var, env[i], ft_strlen(var))
			&& env[i][ft_strlen(var)] == '=')
			i = i + 1;
		if (env[i] == NULL)
			break ;
		newenv[j] = NULL;
		newenv[j] = ft_strdup(env[i]);
		if (!newenv[j])
			return (0);
		j++;
	}
	return (j);
}

static void	pull_from_env(char *var, char **env, t_general *general)
{
	char	**newenv;
	int		res;
	int		i;
	int		j;

	res = 0;
	i = -1;
	while (env[++i])
		res += ft_strlen(env[i]);
	newenv = NULL;
	newenv = (char **)malloc(sizeof(char **) * res * i);
	if (!newenv)
		return ;
	j = init_newenv(newenv, env, var);
	if (!j)
		return ;
	newenv[j++] = NULL;
	free_char_array(env);
	general->env = newenv;
}

void	ft_unset(t_general *general)
{
	if (general->tokens[1] != NULL)
	{
		if (is_env_contain_name(general->tokens[1], general->env))
			pull_from_env(general->tokens[1], general->env, general);
	}
	return ;
}
