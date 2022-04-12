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
			ft_exit("malloc: can't allocate region", 139);
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
	while(env[++i])
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

	paths = NULL;
	temp = NULL;
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

void	ft_show_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
	}
}

void	change_env(char	**env, char *key, char *value)
{
	int	i;
	char *temp;

	key = ft_strjoin(temp, "=");
	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], key, ft_strlen(key)))
		{
			temp = env[i];
			env[i] = ft_strjoin(key, value);
			free(temp);
		}
	}
}
