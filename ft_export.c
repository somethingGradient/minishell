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
void ft_export(t_general *general)
{
	if (!ft_strlen(general->token.to_print))
	{
		char **sortedenv = copy_env(general->env);
		ft_sortenv(sortedenv);
		ft_show_env(sortedenv, general->out_fd);
		free_char_array(sortedenv);
	}

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
		printf("|lol|\n");
	while (i < count)
	{
		j = i + 1; 
		while (j < count)
		{
			if(ft_strcmp(env[j], env[j]) < 0)
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