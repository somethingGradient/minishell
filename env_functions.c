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

	paths = NULL;
	temp = NULL;
	temp = ft_get_env(env, "PATH");
	paths = ft_split(temp, ':');
	free(temp);
	return (paths);
}