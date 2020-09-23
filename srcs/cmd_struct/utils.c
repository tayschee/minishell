#include "minishell.h"

int     this_is_operator(char *cmd, char *operator)
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