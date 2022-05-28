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

char	*ft_get_env(char **env, char *str)
{
	int		i;
	int		len;
	char	*env_value;

	env_value = NULL;
	if (!str)
		return (NULL);
	i = -1;
	len = ft_strlen(str);
	while (env[++i])
	{
		if (ft_strnstr(env[i], str, len))
			env_value = ft_substr(env[i], len + 1, ft_strlen(env[i]) - len);
	}
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
	temp = ft_get_env(env, "PATH");
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

void	change_env(char	**env, char *key, char *value)
{
	int		i;
	char	*temp;

	temp = ft_strjoin(key, "=");
	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], key, ft_strlen(key)))
		{
			env[i] = ft_strjoin(temp, value);
			free(temp);
		}
	}
}
