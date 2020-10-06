#include "minishell.h"

int         this_is_operator(char *cmd, char *operator)
{
    int i;
    int n;
    int j;

    i = 0;
    j = -1;
    while(operator[i])
    {
        n = 0;
        while(operator[i + n] && operator[i + n] != ' ')
            n++;
        j++;
	    if (!ft_strncmp(cmd, &operator[i], n))
		    return (i);
        i += n;
        if (operator[i])
            i++;
    }
    return (-1);
}

int count_struct(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd)
    {
        i++;
        cmd = cmd->next;
    }
    return (i);
}

char    quote_management(char *txt)
{
    char    c;
    int     i;

    i = 0;
    c = 0;
    while (txt[i])
    {
        if (txt[i] == '\\')
            c = txt[i++];
        else if (txt[i] == '"' || txt[i] == '\'')
            c = txt[i];
        while ((c == '"' || c == '\'') && txt[++i])
        {
            if (txt[i] == c)
            {
                c = 0;
                break;
            }
        }
        if (txt[i])
        {
            c = 0;
            i++;
        }
    }
    return (c);
}
