/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 11:23:25 by jannabel          #+#    #+#             */
/*   Updated: 2022/05/28 12:12:07 by jannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer_find_char(char *string, char needle)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == needle || string[i] == D_QUOTE || string[i] == QUOTE)
			return (i);
		if (string[i] == '?')
			return (i + 1);
		i++;
	}
	return (i);
}

int	fixing_for_norminette(t_general *general, char c, char *aux, int nbr)
{
	if (general->token.quote == 0 && (c == QUOTE || c == D_QUOTE))
		general->token.quote = c;
	else
	{
		if (general->token.quote == c)
			general->token.quote = 0;
		else
		{
			aux[nbr] = c;
			nbr++;
		}
	}
	return (nbr);
}

int	cycles_for_tokenizer(t_general *general, char *in, char	*aux, int i, int c)
{
	if (in[0] == '-' && in[1] == 'n')
	{
		general->has_flag = true;
		i += 2;
	}
	while (in[i] == ' ')
		i++;
	while (in[i])
	{
		if (general->token.quote == 0 && (in[i] == QUOTE || in[i] == D_QUOTE))
			general->token.quote = in[i];
		else
		{
			if (general->token.quote == in[i])
				general->token.quote = 0;
			else
			{
				aux[c] = in[i];
				c++;
			}
		}
		i++;
	}
	return (c);
}

void	tokenizer_clean_quotes(t_general *general, char *in)
{
	int		c;
	char	*aux;

	general->token.quote = 0;
	aux = ft_strtrim(in, " ");
	general->has_flag = false;
	c = cycles_for_tokenizer(general, in, aux, 0, 0);
	aux[c] = '\0';
	free(general->token.to_print);
	general->token.to_print = aux;
}

void	tokenizer(t_general *general)
{
	t_token	*tk;

	tk = init_tk();
	general->token.quote = 0;
	tk->end = ft_strdup("");
	if (general->line)
	{
		while ((int)ft_strlen(general->line) > tk->i)
		{
			if (general->token.quote == 0 && (general->line[tk->i] == QUOTE))
				general->token.quote = general->line[tk->i];
			else
			{
				if (general->token.quote == general->line[tk->i])
					general->token.quote = 0;
			}
			tk->len++;
			tk->i++;
		}
		finish_tokenizer(general, tk);
	}
}
