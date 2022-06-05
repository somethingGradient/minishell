/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:12:05 by jannabel          #+#    #+#             */
/*   Updated: 2022/05/28 10:14:50 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char	**env)
{
	char	**copy;
	int		res;
	int		i;

	res = 0;
	i = -1;
	while (env[++i])
		res += ft_strlen(env[i]);
	copy = NULL;
	copy = (char **)malloc(sizeof(char **) * res * i + 1);
	if (!copy)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		copy[i] = NULL;
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
			return (NULL);
	}
	copy[i] = NULL;
	return (copy);
}

char	*ft_get_env_value(char **env, char *str)
{
	int		i;
	int		len;
	char	*env_value;

	env_value = NULL;
	if (!str)
		return (NULL);
	i = -1;
	str = ft_strjoin(str, "=");
	len = ft_strlen(str);
	while (env[++i])
	{
		if (ft_strnstr(env[i], str, len))
		{
			env_value = ft_substr(env[i], len, ft_strlen(env[i]) - len);
			break ;
		}
	}
	free(str);
	str = NULL;
	return (env_value);
}

char	**get_env_paths(char **env)
{
	char	*temp;
	char	**paths;
	int		i;

	temp = NULL;
	paths = NULL;
	if (!env)
		return (NULL);
	temp = ft_get_env_value(env, "PATH");
	if (!temp)
		return (NULL);
	paths = ft_split(temp, ':');
	free(temp);
	i = -1;
	while (paths[++i])
	{
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(temp);
	}
	return (paths);
}

void	ft_show_env(char **env, int out_fd)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		ft_putstr_fd(env[i], out_fd);
		if (ft_strlen(env[i]))
			ft_putchar_fd('\n', out_fd);
	}
}

void	change_env(t_general *general, char *key, char *value)
{
	int		i;
	char	*temp;
	char	*temp2;

	temp = NULL;
	temp2 = NULL;
	temp = ft_strjoin(key, "=");
	if (!value)
		temp2 = NULL;
	else
		temp2 = ft_strjoin(temp, value);
	i = -1;
	while (general->env[++i])
	{
		if (ft_strnstr(general->env[i], temp, ft_strlen(temp)))
		{
			free(temp);
			temp = general->env[i];
			break ;
		}
	}
	free(general->env[i]);
	general->env[i] = temp2;
	temp2 = NULL;
	temp = NULL;
}
