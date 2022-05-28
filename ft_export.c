/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:42:35 by jannabel          #+#    #+#             */
/*   Updated: 2022/05/28 12:52:33 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_show_env_withprefix(char **env, int out_fd)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", out_fd);
		while (env[i][j])
		{
			ft_putchar_fd(env[i][j], out_fd);
			if (env[i][j] == '=')
			{
				ft_putchar_fd('\"', out_fd);
			}
			j++;
		}
		ft_putchar_fd('\"', out_fd);
		if (ft_strlen(env[i]))
			ft_putchar_fd('\n', out_fd);
		i++;
	}
}

static int	check_name(char *name, char **env)
{
	int	j;

	j = 0;
	while (name[j])
	{
		if (!ft_isalnum((int)name[j]) && name[j] != '_')
		{
			ft_putstr_fd("Invalid variable name\n", 1);
			free(name);
			return (1);
		}
		j++;
	}
	j = 0;
	while (env[j])
	{
		if (!ft_strncmp(env[j], name, ft_strlen(name)))
		{
			free(name);
			return (1);
		}
		j++;
	}
	return (0);
}

static void	put_var_to_env(char **env, char *var, t_general *general)
{
	char	**newenv;
	int		res;
	int		i;

	res = 0;
	i = -1;
	while (env[++i])
		res += ft_strlen(env[i]);
	res += ft_strlen(var);
	newenv = NULL;
	newenv = (char **)malloc(sizeof(char **) * res * i + 2);
	if (!newenv)
		return ;
	i = -1;
	while (env[++i])
	{
		newenv[i] = NULL;
		newenv[i] = ft_strdup(env[i]);
		if (!newenv[i])
			return ;
	}
	newenv[i++] = ft_strdup(var);
	newenv[i++] = NULL;
	free_char_array(env);
	general->env = newenv;
}

static void	ft_sortenv(char **env)
{
	int		i;
	int		j;
	int		count;
	int		temp;
	char	*tmpstr;

	i = -1;
	count = 0;
	while (env[count])
		count++;
	while (++i < count)
	{
		j = i + 1;
		while (j < count)
		{
			temp = ft_strcmp(env[i], env[j]);
			if (temp > 0)
			{
				tmpstr = env[i];
				env[i] = env[j];
				env[j] = tmpstr;
			}
			j++;
		}
	}
}

void	ft_export(t_general *general)
{
	int		i;
	char	**unsortedenv;
	char	*name;

	i = 0;
	if (!ft_strlen(general->token.to_print))
	{
		unsortedenv = copy_env(general->env);
		ft_sortenv(unsortedenv);
		ft_show_env_withprefix(unsortedenv, general->out_fd);
		free_char_array(unsortedenv);
	}
	else
	{
		if (!general->tokens[1] || !ft_strrchr(general->tokens[1], (int) '='))
			return ;
		while (general->tokens[1][i] && general->tokens[1][i] != '=')
			i++;
		name = ft_substr(general->tokens[1], 0, i);
		if (check_name(name, general->env))
			return ;
		put_var_to_env(general->env, general->tokens[1], general);
	}
}
