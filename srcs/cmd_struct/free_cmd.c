/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 16:23:38 by abarot            #+#    #+#             */
/*   Updated: 2020/10/02 16:23:39 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    free_char_2(char **txt, int nul)
{
    int i;

    i = 0;
    if (txt)
    {
        while(txt[i])
        {
            free(txt[i]);
            i++;
        }
        if (!nul)
            free(txt);
    }
}

static void     free_rdr_list(t_rdr **rdr)
{
    t_rdr   *save;
    t_rdr   *before;

    save = *rdr;
    while (*rdr)
    {
        before = NULL;
        while ((*rdr)->next)
        {
            before = *rdr;
            *rdr = (*rdr)->next;
        }
        /*printf("cmd : %p\n", *cmd);
        printf("char : %s\n", (*cmd)->argv[0]);
        printf("before 2 : %p\n", before);*/
        free((*rdr)->path);
        free(*rdr);
        if (before)
        {
            before->next = NULL;
            *rdr = save;
        }
        else
            *rdr = NULL; 
    }

}

static void     free_cmd(t_cmd *cmd, int nul)
{
    free_char_2(cmd->argv, nul);
    free_rdr_list(&cmd->rdr);
    cmd->rdr = NULL;
    free(cmd);
}

void            free_cmd_list(t_cmd **cmd)
{
    int     nul;
    t_cmd   *save;
    t_cmd   *before;

    nul = 0;
    save = *cmd;
    while (*cmd)
    {
        before = NULL;
        while ((*cmd)->next)
        {
            before = *cmd;
            *cmd = (*cmd)->next;
        }
        /*printf("cmd : %p\n", *cmd);
        printf("char : %s\n", (*cmd)->argv[0]);
        printf("before 2 : %p\n", before);*/
        if (before)
            nul = 1;
        free_cmd(*cmd, nul);
        if (before)
        {
            before->next = NULL;
            *cmd = save;
        }
        else
            *cmd = NULL; 
    }
}