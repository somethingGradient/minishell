/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:15:19 by jannabel          #+#    #+#             */
/*   Updated: 2022/05/28 12:15:47 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_tk(void)
{
	t_token	*tk;

	tk = NULL;
	tk = (t_token *)malloc(sizeof(t_token));
	tk->end = NULL;
	tk->new = NULL;
	tk->to_exec = NULL;
	tk->to_print = NULL;
	tk->quote = '\0';
	tk->i = 0;
	tk->init = 0;
	tk->len = 1;
	tk->posic = 0;
	return (tk);
}

static void	free_tk(t_token *tk)
{
	if (tk->end != NULL)
	{
		free(tk->end);
		tk->end = NULL;
	}
	if (tk->new != NULL)
	{
		free(tk->new);
		tk->new = NULL;
	}
	if (tk->to_exec != NULL)
	{
		free(tk->to_exec);
		tk->to_exec = NULL;
	}
	if (tk->to_print != NULL)
	{
		free(tk->to_print);
		tk->to_print = NULL;
	}
	free(tk);
	tk = NULL;
}

void	finish_tokenizer(t_general *general, t_token *tk)
{
	char	*temp;

	tk->new = ft_substr(general->line, tk->init, tk->len);
	temp = tk->end;
	tk->end = ft_strjoin(tk->end, tk->new);
	free(temp);
	temp = NULL;
	tk->posic = tokenizer_find_char(tk->end, ' ');
	general->token.to_print = ft_strtrim(&(tk->end)[tk->posic], " ");
	general->token.to_exec = ft_substr(tk->end, tk->i + 1, tk->posic);
	tokenizer_clean_quotes(general, general->token.to_print);
	general->tokens = ft_split(tk->end, ' ');
	free(general->line);
	general->line = NULL;
	free_tk(tk);
}
