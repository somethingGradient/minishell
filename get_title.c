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

char	*get_username(void)
{
	char	*temp;
	char	*name;

	name = ft_strjoin(BEGIN(49, 32), getenv("USER"));
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

char	*get_cwd(char *cwd)
{
	char	*temp;

	temp = NULL;
	if (!cwd)
		temp = getcwd(NULL, 512);
	else
		temp = cwd;
	cwd = ft_strjoin(BEGIN(49, 34), temp);
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

char	*get_title(t_general *general, char *cwd)
{
	char	*title;
	char	*username;

	username = get_username();
	if (!username)
		return (NULL);
	cwd = get_cwd(cwd);
	if (!cwd)
	{
		free(username);
		return (NULL);
	}
	title = ft_strjoin(username, cwd);
	free(username);
	free(cwd);
	return (title);
}
