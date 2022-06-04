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

static void pull_from_env(int k, char *var, char **env, t_general *general)
{
	char	**newenv;
	int		res;
	int		i;
	int     j;
	res = 0;
	i = -1;
	while (env[++i])
		res += ft_strlen(env[i]);
	res += ft_strlen(var);
	newenv = NULL;
	newenv = (char **)malloc(sizeof(char **) * res * i);
	if (!newenv)
		return ;
	i = -1;
	j = 0;
	while (env[++i])
	{
		if (!strcmp(var, env[i]))
			i = i + 1;
		newenv[j] = NULL;
		newenv[j] = ft_strdup(env[i]);
		if (!newenv[j])
			return ;
		j++;
	}
	newenv[j++] = NULL;
	free_char_array(env);
	general->env = newenv;
}

void	ft_unset(t_general *general)
{
	int		i;
	if (general->tokens[1] != NULL)
	{
		i = -1;
		while (general->env[++i])
		{
			if (!ft_strncmp(general->tokens[1], general->env[i], ft_strlen(general->tokens[1]))
				&& general->env[i][ft_strlen(general->tokens[1])] == '=')
			{
				pull_from_env(i, general->env[i], general->env, general);
				break ;
			}
		}
	}
}
