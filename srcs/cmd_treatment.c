/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:12:53 by abarot            #+#    #+#             */
/*   Updated: 2020/10/02 14:26:57 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int             **pipe_for_fork(int i)
{
        int    **p_fd;
        int     fd[i][2];
        int		j;

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

static void     redirect_stdin_stdout(int *p_fd[2], t_cmd *cmd, int mlc_size, int i)
{
        int pos;

        pos = mlc_size - i;
        if (!g_shell.cpid && !cmd->next)
			ft_replace_stdfd(p_fd[pos]);
        else if (!g_shell.cpid)
                dup2(p_fd[pos - 1][1], STDOUT_FILENO);
        else if (!cmd->next) 
                dup2(p_fd[pos][0], STDIN_FILENO);
        else
        {
                dup2(p_fd[pos][0], STDIN_FILENO);
                dup2(p_fd[pos - 1][1], STDOUT_FILENO);
        }
        i = 0;
        while (i < mlc_size)
        {
                close(p_fd[i][0]);
                close(p_fd[i][1]);
                i++;
        }
}

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
        return (cmd);
}

int             ft_cmd_treatment(t_cmd *cmd)
{
	if (!cmd)
		return (EXIT_FAILURE);
	else if  (!cmd->next && cmd->type == CMD)
	{
		if (cmd->rdr)
			ft_manage_rdr(cmd);
		else
			ft_redirect_cmd(cmd);
	}
	else
	{
		ft_exec(cmd);
	}
	if (g_shell.status && cmd->type == PATH)
	{
		ft_putstr_fd(cmd->argv[0], STDOUT_FILENO);
		ft_putstr_fd(": command not found\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
