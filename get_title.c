/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_title.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:27:12 by jannabel          #+#    #+#             */
/*   Updated: 2022/05/28 14:27:39 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_username(void)
{
	char	*temp;
	char	*name;

	temp = NULL;
	name = NULL;
	name = ft_strjoin(GREEN, getenv("USER"));
	free(temp);
	if (!name)
		return (NULL);
	temp = name;
	name = ft_strjoin(name, CLOSE);
	free(temp);
	if (!name)
		return (NULL);
	temp = name;
	name = ft_strjoin(name, ":");
	free(temp);
	if (!name)
		return (NULL);
	return (name);
}

static char	*check_home(t_general *general, char *cwd)
{
	char	*temp;
	char	*temp2;

	temp = NULL;
	temp2 = NULL;
	if (!cwd)
		temp = getcwd(NULL, 512);
	else
		temp = cwd;
	if (!ft_strncmp(general->home, temp, ft_strlen(general->home)))
	{
		temp2 = ft_substr(temp, ft_strlen(general->home), ft_strlen(temp));
		free(temp);
		temp = NULL;
		temp = ft_strdup("~");
		cwd = temp;
		temp = ft_strjoin(temp, temp2);
		free(cwd);
		free(temp2);
		cwd = NULL;
		temp2 = NULL;
	}
	return (temp);
}

static char	*get_cwd(t_general *general, char *cwd)
{
	char	*temp;

	temp = check_home(general, cwd);
	cwd = ft_strjoin(BLUE, temp);
	free(temp);
	if (!cwd)
		return (NULL);
	temp = cwd;
	cwd = ft_strjoin(cwd, CLOSE);
	free(temp);
	if (!cwd)
		return (NULL);
	temp = cwd;
	cwd = ft_strjoin(cwd, "$ ");
	free(temp);
	if (!cwd)
		return (NULL);
	return (cwd);
}

static void	concat(t_general *general, char *username, char *cwd)
{
	if (!username || !cwd)
	{
		if (username)
			free(username);
		if (cwd)
			free(cwd);
		username = NULL;
		cwd = NULL;
		return ;
	}
	else
		general->title = ft_strjoin(username, cwd);
	free(username);
	free(cwd);
}

void	get_title(t_general *general, char *cwd)
{
	if (general->title)
	{
		free(general->title);
		general->title = NULL;
	}
	concat(general, get_username(), get_cwd(general, cwd));
}
