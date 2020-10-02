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

static char     *cmd_without_bs2(char *cmd, int i)
{
    int j;
    char *cmd_without_bs;

    j = 0;
    if (!(cmd_without_bs = ft_calloc(sizeof(char), (i + 1))))
        return (NULL);
    i = 0;
    while (cmd[i])
    {
        if (cmd[i] != '\\')
        {
            cmd_without_bs[j] = cmd[i];
            j++;
        }
        i++;
    }
    free(cmd);
    return(cmd_without_bs);


}

char            *cmd_without_bs(char *cmd)
{
    int i;
    int j;
    int bs;

    i = 0;
    j = 0;
    bs = 0;
    if (cmd)
    {
        while (cmd[i])
        {
            if (cmd[i] == '\\')
            {
                bs = 1;
                j++;
            }
            i++;
        }
        if (bs == 1)
            return(cmd_without_bs2(cmd, j));
        return (cmd);
    }
    return (NULL);
}
