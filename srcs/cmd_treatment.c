/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:12:53 by abarot            #+#    #+#             */
/*   Updated: 2020/10/02 11:00:00 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*j'avais plus de place dans ma fonction juste renvoie
dans ft_manage_redirection*/
/*static void             redirection(t_cmd *cmd, int **p_fd, int mlc_size, int i)
{
        int pos;

        pos = mlc_size - i;
        if (g_shell.cpid)
                wait(&g_shell.cpid);
        ft_manage_rdr(cmd, pfd[pos]);
        free(p_fd);

}*/

/*compte le nombre de pipe necessaire*/
static int             **pipe_for_fork(int i)
{
        int    **p_fd;
        int     fd[i][2];
        int j;

        j = 0;
        if (!(p_fd = malloc(sizeof(int *) * (i)))) 
                return (NULL);
        while (j < i)
        {
                pipe(fd[j]);
                p_fd[j] = fd[j];
                j++;
        }
        return (p_fd);
}

/* fonction uniquement destine a rediriger les sortie dans les pipes*/
static void     redirect_stdin_stdout(int *p_fd[2], t_cmd *cmd, int mlc_size, int i)
{
        int pos;

        pos = mlc_size - i;
        if (!g_shell.cpid && !cmd->next)
        {
                dup2(p_fd[pos][0], 0);
                dup2(p_fd[pos][1], 1);
        }
        else if (!g_shell.cpid)
                dup2(p_fd[pos - 1][1], 1);
        else if (!cmd->next) 
                dup2(p_fd[pos][0], 0);
        else
        {
                dup2(p_fd[pos][0], 0);
                dup2(p_fd[pos - 1][1], 1);
        }
        i = 0;
        while (i < mlc_size)
        {
                close(p_fd[i][0]);
                close(p_fd[i][1]);
                i++;
        }
}

/*fork une par une chaque commande et fait des pipes pour les reliers*/
t_cmd           *fork_all(t_cmd *cmd)
{
        int     i;
        int     j;
        int     mlc_size;
        int     **p_fd;

        i = count_struct(cmd) - 1;
        j = 0;
        if ((mlc_size = i) + 1 > 0)
                p_fd = pipe_for_fork(mlc_size);
        while (i > 0 && !g_shell.cpid)
        {
                g_shell.cpid = fork();
                if (g_shell.cpid)
                        break;
                i--;
        }
        while (j < i)
        {
                cmd = cmd->next;
                j++;
        }
        if (mlc_size > 0)
                redirect_stdin_stdout(p_fd, cmd, mlc_size, i);
        //redirection(cmd, p_fd, mlc_size, i);
        return (cmd);
}

/* fonction qui permet l'execution de toute les commandes*/
int             ft_cmd_treatment(t_cmd *cmd)
{

        if (cmd)
        {
                ft_exec(cmd);
        }
        return (EXIT_SUCCESS);
}
