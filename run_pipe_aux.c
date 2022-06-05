/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:27:58 by jannabel          #+#    #+#             */
/*   Updated: 2022/05/28 14:28:00 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_descriptor_handler(int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	return (0);
}

void	spaces_in_pipe(t_general *general, int i, char *command)
{
	char	*aux;

	if (ft_strlen(general->token.to_print) && general->tokens[i]
		&& (general->tokens[i][0] == QUOTE || general->tokens[i][0] == D_QUOTE))
		aux = ft_strtrim(general->token.to_print, D_QUOTE_S);
	else
		aux = ft_strtrim(general->tokens[i], D_QUOTE_S);
	free(general->tokens[i]);
	general->tokens[i] = aux;
	command = ft_strjoin(command, general->tokens[i - 1]);
	g_exit_code = execve(command, &general->tokens[i - 1], general->env);
	free(command);
}

void	execve_error(t_general *general)
{
	g_exit_code = 127;
	if (general->tokens[0][0] != '|')
		printf("minishell: %s: %s", general->tokens[0], ERROR_CMD);
	else if (general->tokens[1])
		printf("minishell: %s: %s", general->tokens[1], ERROR_CMD);
}

void	expr_utils(t_general *general, int j)
{
	char	*temp;

	temp = NULL;
	if (general->tokens[0][0] == '|')
		j = 1;
	while (general->tokens[++j])
	{
		if ((general->tokens[j][0] == '$' && general->tokens[j][1] == '?')
			&& ft_strlen(general->tokens[j]) == 2)
			general->tokens[j] = ft_itoa(g_exit_code);
		else if (general->tokens[j][0] == '$'
			&& ft_isalpha(general->tokens[j][1]))
		{
			temp = ft_get_env_value(general->env, &general->tokens[j][1]);
			free(general->tokens[j]);
			general->tokens[j] = temp;
			temp = NULL;
		}
	}
	g_exit_code = 127;
}
