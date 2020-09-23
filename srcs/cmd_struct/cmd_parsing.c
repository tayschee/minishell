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

    if (!(new_cmd = ft_calloc(j + 1, sizeof(char))))
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

/*verifie qu'il n'y ai pas de direction dans le vent*/
static int    check_error_rdr(char **cmd)
{
    int i;

    i = 0;
    if (cmd)
    {
        while (cmd[i])
        {
            if (this_is_operator(cmd[i], RDR_LIST) >= 0
            && (!cmd[i + 1] || this_is_operator(cmd[i + 1],
            OPERATOR_LIST) > 0))
            {
                write(1, UNEXPECTED_NEWLINE,
                ft_strlen(UNEXPECTED_NEWLINE));
                return (1); //fonction exit free all
            }
            /*pas sur que ce qu'il y a en dessous est utile verifie que a gauche de |
            il y a qqc*/
            if (!ft_strncmp(cmd[i], "|", 2) && (i == 0 || this_is_operator(cmd[i - 1],
            OPERATOR_LIST)> 0))
            {
                write(1, UNEXPECTED_NEWLINE,
                ft_strlen(UNEXPECTED_NEWLINE));
                return (1); //fonction exit free all
            }
            i++;
        }
    }
    return (-1);
}


/*transforme cmd en un char** de mot avec < > | << >> || 
compris comme un seul mot
les deux fonctions au dessus sont utiles*/
t_cmd    *ft_init_cmd(char *unique_cmd)
{
    //int  i;
    char *cmd_sentence;
    char **cmd_divise;
    t_cmd   *cmd;

    //i = 0;
    cmd = NULL;
    cmd_sentence = split_word(unique_cmd, "<>|"); ///mistake here
    cmd_divise = ft_split(cmd_sentence, ' ');
    if (cmd_sentence)
        free(cmd_sentence);
    if (check_error_rdr(cmd_divise) < 0)
        cmd = char_to_struct_cmd(cmd_divise);
    /*while (cmd)
    {
        i = 0;
        while (cmd->argv[i])
        {
            printf("%s ", cmd->argv[i]);
            i++;
        }
        printf ("\n");
        printf("rdr : %p\n",cmd->rdr);
        printf("next : %p\n", cmd->next);
        printf("rdr :\n");
        while(cmd->rdr)
        {
            printf("\te_type : %d\n", cmd->rdr->e_rdr);
            printf("\trdr path : %s\n", cmd->rdr->path);
            printf("\trdr next : %p\n", cmd->rdr->next);
            cmd->rdr = cmd->rdr->next;
            printf("ok\n");

        }
        cmd = cmd->next;
    }*/
    free_cmd_list(&cmd);
    //printf("cmd null : %p\n", cmd);
    return (cmd);
}