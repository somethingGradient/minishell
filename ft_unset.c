#include "minishell.h"

void ft_unset(t_general *general)
{
    if (ft_strlen(general->token.to_print))
    {
        int i;

        i = 0;
        while (general->env[i])
        {
            char **envname = ft_split(general->env[i], '=');
            if(!ft_strcmp(general->token.to_print, envname[0]))
            {
                general->env[i] = "\0";
                break;
            }
            i++;
        }
        return ;
    }
    else
    {
        ft_putstr_fd("unset: not enough arguments\n", 1);
    }
}