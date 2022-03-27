
#include "minishell.h"

int	ft_cd(t_general *general)
{
	char *buf;
	char *temp;

	if (ft_strlen(general->line) <= 3)
	{
		printf("Error!");
		return (-1);
	}
	buf = ft_calloc(128, sizeof(char));
	getcwd(buf, 128);
	temp = general->line + 3;
	if (chdir(temp) < 0)
	{
		ft_putstr_fd("No such file or directory.\n", 2);
		return (-1);	
	}
	general->title = get_title(getenv("CWD"));
	temp = getcwd(NULL, 512);
	change_env(general->env, "PWD", temp);
	free(temp);
	return (0);
}