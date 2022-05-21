
#include "minishell.h"

char	*get_cd_buf(t_general *general, char *cwd, char *user, int mode)
{
	char	*buf;
	char	*temp;

	buf = NULL;
	temp = NULL;
	if (mode)
	{
		user = ft_get_env(general->env, "USER");
		if (cwd[1] == 'U')
			temp = ft_strjoin("/Users/", user);
		else if (cwd[1] == 'h')
			temp = ft_strjoin("/home/", user);
		free(user);
		buf = ft_strjoin(temp, "/");
	}
	else
	{
		if (general->token.to_print[0] == '/')
			cwd[ft_strlen(cwd) - 1] = '\0';
		temp = ft_strjoin(cwd, "/");
		buf = ft_strjoin(temp, general->token.to_print);
	}
	free(temp);
	return (buf);
}

void	ft_cd(t_general *general)
{
	char	*buf;
	char	*cwd;

	buf = NULL;
	cwd = NULL;
	cwd = getcwd(NULL, 512);
	if (ft_strlen(general->tokens[0]) &&
			(!ft_strlen(general->token.to_print) ||
				(ft_strlen(general->token.to_print) == 1
					&& general->token.to_print[0] == '~')))
		buf = get_cd_buf(general, cwd, NULL, 1);
	else
		buf = get_cd_buf(general, cwd, NULL, 0);
	if (chdir(buf) < 0)
	{
		printf("ALO\n");
		ft_putstr_fd("No such file or directory.\n", 1);
		g_ret_number = 1;
		return ;
	}
	buf[ft_strlen(buf) - 1] = '\0';
	cwd = getcwd(NULL, 512);
	change_env(general->env, "PWD", cwd);
	general->title = get_title(cwd);
}

void	ft_pwd(t_general *general)
{
	char	*temp;

	temp = ft_get_env(general->env, "PWD");
	ft_putstr_fd(temp, general->out_fd);
	ft_putstr_fd("\n", general->out_fd);
	free(temp);
	g_ret_number = 0;
}