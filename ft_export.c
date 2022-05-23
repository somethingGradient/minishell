#include "minishell.h"

// int	ft_export(t_general *general)
// {
// 	int		i;
// 	int		k;
// 	char	**temp;
// 	char	**edited_env;

// 	i = -1;

// 	if (ft_strlen(general->cmd) == 6 && !general->split_line[1])
// 	{
// 		while (general->env[++i])
// 		{
// 			ft_putstr_fd("declare -x ", 1);
// 			ft_putstr_fd(general->env[i], 1);
// 			ft_putchar_fd('\n', 1);
// 		}
// 		return (0);
// 	}
// 	else
// 	{
// 		int str_lens = 0;
		
// 		int i = 0;

// 		char *key = NULL;
// 		char *value = NULL;

// 		k = 5;

// 		while (general->line[++k] == ' ') ;

// 		if (general->line[k] == '\'' || general->line[k] == '"')
// 			k++;
// 		else if (general->line[k] == '#')
// 		{
// 			general->line[6] = '\0';
// 			ft_export(general);
// 			return (0);
// 		}

// 		if (!ft_isalpha(general->line[k]))
// 		{
// 			ft_putstr_fd("bash: export: `", 1);
// 			ft_putchar_fd(general->line[k], 1);
// 			ft_putstr_fd(": not a valid identifier\n", 1);
// 			return (-1);
// 		}

// 		int	j = k;

// 		while (ft_isalnum(general->line[k]) && general->line[k++] != '=') ;

// 		key = ft_substr(general->line, j, k - j);

// 		j = ++k;
// 		while (ft_isalnum(general->line[k++]));
// 		value = ft_substr(general->line, j, k - j - 1);
// 		value = ft_strjoin("\"", value);
// 		value = ft_strjoin(value, "\"");

// 		char *res;
// 		res = ft_strjoin(key, "=");
// 		res = ft_strjoin(res, value);


// 		temp = general->env;
// 		while (general->env[++i])
// 		{
// 			k = -1;
// 			while (general->env[i][++k])
// 				str_lens += k;
// 		}

// 		edited_env = (char **)malloc(sizeof(char) * (i + 1) * k);
// 		edited_env[i + 1] = NULL;

// 		i = -1;
// 		while (general->env[++i])
// 			edited_env[i] = ft_strdup(general->env[i]);

// 		edited_env[i] = res;
// 		general->env = edited_env;

// 	}

// 	return (0);
// }

void	ft_show_env_withprefix(char **env, int out_fd)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		ft_putstr_fd("declare -x ", out_fd);
		ft_putstr_fd(env[i], out_fd);
		if (ft_strlen(env[i]))
			ft_putchar_fd('\n', out_fd);
	}
}

int		check_name(char *name)
{
	int j;

	j = 0;
	while (name[j])
	{
		if (!ft_isalnum((int)name[j]) && name[j] != '_')
		{
			ft_putstr_fd("Invalid variable name\n", 1);
			return (1);
		}
		j++;
	}
	return (0);
}

void ft_export(t_general *general)
{
	printf("|%s|\n", general->tokens[0]);
	printf("|%s|\n", general->tokens[1]);
	int	i;

	i = 0;
	if (!ft_strlen(general->token.to_print))
	{
		char **unsortedenv = copy_env(general->env);
		ft_sortenv(unsortedenv);
		//char **sortedenv = ft_addprefix(unsortedenv);
		ft_show_env_withprefix(unsortedenv, general->out_fd);
		free_char_array(unsortedenv);
	}
	else
	{
		printf("|lol|\n");
		if (!general->tokens[1] || !ft_strrchr(general->tokens[1], (int)'='))
			return ;
		while (general->tokens[1][i] && general->tokens[1][i] != '=')
			i++;
		char *name = ft_substr(general->tokens[1], 0, i);
		printf("|%s|\n", name);
		if (check_name(name))
		{
			free(name);
			return ;
		}
		
	}
}

char **ft_addprefix(char **env)
{
	int i;
	char **newenv;

	i = 0;
	while(env[i])
	{
		//newenv[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + ft_strlen("declare -x ")));
		newenv[i] = ft_strjoin("declare -x ", env[i]);
		i++;
	}
	free_char_array(env);
	return (newenv);
} 

void ft_sortenv(char **env)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (env[count])
		count++;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			int temp  = ft_strcmp(env[i], env[j]);
			if(temp > 0)
			{
				char *tmpstr;
				tmpstr = env[i];
                env[i] = env[j];
				env[j] = tmpstr;
            }
			j++;
		}
		i++;
	}
}