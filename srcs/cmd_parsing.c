#include "minishell.h"

/*separe tout les mots par un espace < > | << >> || sont des mots*/

static int     cmp_letter(char c, char *operator)
{
    int i;

    i = 0;
    while(operator[i])
    {
        if(c == operator[i])
            return (1);
        i++;
    }
    return (0);
}

static char *cmd_with_split_word(char *cmd, char *operator, int j)
{
    int     i;
    char    *new_cmd;

    if (!(new_cmd = ft_calloc(j, sizeof(char))))
        return (NULL);
    i = 0;
    j = 0;
    while (cmd[i])
    {
        if (cmp_letter(cmd[i], operator))
        {
            if (i == 0 || (cmd[i - 1] != ' ' && cmd[i] != cmd[i - 1]))
                new_cmd[j++] = ' ';
            new_cmd[j] = cmd[i];
            if (cmd[i + 1] != cmd[i] && cmd[i + 1] != ' ')
                new_cmd[++j] = ' ';
        }
        else
            new_cmd[j] = cmd[i];
        j++;
        i++;
    }
    return (new_cmd);
}

static char *split_word(char *cmd, char *operator)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(cmd[i])
    {
        if (cmp_letter(cmd[i], operator))
        {
            if (i == 0 || (cmd[i - 1] != ' ' && cmd[i] != cmd[i - 1]))
                j++;  
            if (cmd[i + 1] != cmd[i] && cmd[i + 1] != ' ')
                j++;
        }
        j++;
        i++;
    }
    return(cmd_with_split_word(cmd, operator, j));
}




/*transforme cmd en un char** de mot avec < > | << >> || 
compris comme un seul mot
les deux fonctions au dessus sont utiles*/

void    subdivise_cmd(char *unique_cmd)
{
    int  i;
    char *cmd_sentence;
    char **cmd_divise;

    i = 0;
    cmd_sentence = split_word(unique_cmd, "<>|");
    cmd_divise = ft_split(cmd_sentence, ' ');
    while (cmd_divise && cmd_divise[i])
    {
        printf("cmd : %s\n", cmd_divise[i]);
        i++;
    }
    ft_init_cmd(cmd_divise);
}