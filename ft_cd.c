
#include "minishell.h"

int	ft_cd(t_general *general)
{
	char *buf;
	char *temp;

	// printf("|%s|\n", general->token.to_print);
	// printf("|%s|\n", general->tokens[0]);

	// if (ft_strlen(general->tokens[0]) && ft_strlen(general->token.to_print))
	// {

	// 	buf = ft_get_env(general->env, "PWD");
	// 	temp = ft_strjoin(buf, "/");
	// 	free(buf);
	// 	buf = ft_strjoin(temp, general->token.to_print);
	// 	free(temp);


	// 	// printf("|%s|\n", buf);
	// 	// if (chdir(buf) < 0)
	// 	// {
	// 	// 	ft_putstr_fd("No such file or directory.\n", 2);
	// 	// 	return (-1);	
	// 	// }

	// 	printf("|%s|\n", getcwd(buf, 128));

	// 	// change_env(general->env, "PWD", buf - 1);
		
	// }

	// general->title = get_title(getenv("CWD"));
	// temp = getcwd(NULL, 512);
	
	// free(temp);
	// return (0);

	// change_env(general->env, "PWD", temp);

	char *user = NULL;

	if (ft_strlen(general->tokens[0]) && !ft_strlen(general->token.to_print))
	{
		buf = ft_get_env(general->env, "PWD");
		user = ft_get_env(general->env, "USER");

		if (buf[1] == 'U')
			temp = ft_strjoin("/Users/", user);
		else if (buf[1] == 'h')
			temp = ft_strjoin("/home/", user);
		free(buf);
		free(user);
		buf = ft_strjoin(temp, "/");
		if (chdir(buf) < 0)
		{
			ft_putstr_fd("No such file or directory.\n", 2);
			return (-1);	
		}
		change_env(general->env, "PWD", buf);
	}
	else
	{
		buf = ft_calloc(128, sizeof(char));
		getcwd(buf, 128);
		temp = general->line + 3;
		if (chdir(temp) < 0)
		{
			ft_putstr_fd("No such file or directory.\n", 2);
			return (-1);	
		}
	}

	// general->title = get_title(getenv("CWD"));
	// temp = getcwd(NULL, 512);
	// change_env(general->env, "PWD", temp);
	// free(temp);
	return (0);
}





int	ft_pwd(t_general *general)
{
	char	*temp;

	temp = ft_get_env(general->env, "PWD");
	ft_putstr_fd(temp, general->out_fd);
	ft_putstr_fd("\n", general->out_fd);
	free(temp);
}