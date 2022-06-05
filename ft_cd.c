/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:26:49 by akitty            #+#    #+#             */
/*   Updated: 2022/05/28 16:26:51 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cd_buf(t_general *general, char *cwd, int mode)
{
	char	*buf;
	char	*temp;

	buf = NULL;
	temp = NULL;
	if (mode)
	{
		temp = ft_get_env_value(general->env, "HOME");
		buf = ft_strjoin(temp, "/");
		free(temp);
		temp = NULL;
	}
	else
	{
		if (general->token.to_print[0] == '/')
			cwd[ft_strlen(cwd) - 1] = '\0';
		temp = ft_strjoin(cwd, "/");
		buf = ft_strjoin(temp, general->token.to_print);
	}
	free(temp);
	temp = NULL;
	return (buf);
}

static char	*select_buf(t_general *general, char *cwd)
{
	if (ft_strlen(general->tokens[0])
		&& (!ft_strlen(general->token.to_print)
			|| (ft_strlen(general->token.to_print) == 1
				&& general->token.to_print[0] == '~')))
		return (get_cd_buf(general, cwd, 1));
	else
		return (get_cd_buf(general, cwd, 0));
}

void	ft_cd(t_general *general)
{
	char	*buf;
	char	*cwd;

	buf = NULL;
	cwd = NULL;
	if (chdir(general->token.to_print) < 0)
	{
		cwd = getcwd(NULL, 512);
		buf = select_buf(general, cwd);
		if (chdir(buf) < 0)
		{
			ft_putstr_fd("Invalid directory.\n", 2);
			g_exit_code = 1;
		}
		free(buf);
		free(cwd);
		buf = NULL;
		cwd = NULL;
	}
	cwd = getcwd(NULL, 512);
	change_env(general, "PWD", cwd);
	get_title(general, cwd);
}

void	ft_pwd(t_general *general)
{
	char	*temp;

	temp = NULL;
	temp = ft_get_env_value(general->env, "PWD");
	ft_putstr_fd(temp, general->out_fd);
	ft_putstr_fd("\n", general->out_fd);
	free(temp);
	temp = NULL;
	g_exit_code = 0;
}
