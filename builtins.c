#include "minishell.h"

void	is_builtin(char *cmd, t_general *general)
{
	if ((!ft_strncmp("echo", cmd, 4) && ft_strlen(cmd) == 4)
		|| (!ft_strncmp("cd", cmd, 2) && ft_strlen(cmd) == 2)
		|| (!ft_strncmp("pwd", cmd, 3) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp("export", cmd, 6) && ft_strlen(cmd) == 6)
		|| (!ft_strncmp("unset", cmd, 5) && ft_strlen(cmd) == 5)
		|| (!ft_strncmp("env", cmd, 3) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp("exit", cmd, 4) && ft_strlen(cmd) == 4))
		general->is_builtin = true;
	else
		general->is_builtin = false;
}

void	run_builtin(t_general *general)
{
	if (!ft_strncmp(general->tokens[0], "exit", 4))
		ft_exit2(general);
	/*if (!ft_strncmp(general->tokens[0], "pwd", 3))
		ft_pwd(general);*/
	if (!ft_strncmp(general->tokens[0], "echo", 4))
		ft_echo(general);
	if (!ft_strncmp(general->tokens[0], "cd", 2))
		ft_cd(general);
	if (!ft_strncmp(general->tokens[0], "env", 3))
		ft_show_env(general->env);
	if (!ft_strncmp(general->tokens[0], "export", 6))
		ft_export(general);
	/*if (!ft_strncmp(general->tokens[0], "unset", 5))
		ft_unset(general);*/
}