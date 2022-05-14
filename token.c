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

void	tokenizer_clean_quotes(t_general *general, char *in)
{
	int		i;
	int		c;
	char	*aux;

	i = 0;
	c = 0;
	general->token.quote = 0;
	aux = ft_strtrim(in, " ");
	general->has_flag = false;
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
				// if (general->line[tk->i] == '~' && general->token.quote == 0)
				// 	get_home_sign(general, tk);
				// else if (general->line[tk->i] == '$' && general->token.quote == 0)
				// 	get_dollar_sign(general, tk);
			}
			tk->len++;
			tk->i++;
		}
		finish_tokenizer(general, tk);
	}
}
