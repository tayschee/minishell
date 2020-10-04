/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 17:03:57 by abarot            #+#    #+#             */
/*   Updated: 2020/10/05 00:16:44 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_conditionnal(t_cmd *cmd)
{
	if (cmd->type == CMD)
	{
		if (cmd->rdr)
			exit(ft_manage_rdr(cmd));
		else
			exit(ft_redirect_cmd(cmd));
	}
	else
	{
		if (cmd->rdr)
			exit(ft_manage_rdr(cmd));
		else
			exit(ft_exec_paths(cmd));
	}
}

void	pipe_loop(t_cmd *cmd, t_list *pid_lst, int *fd_current, int *fd_prev)
{
	while (cmd->next)
	{
		pipe(fd_current);
		g_shell.cpid = fork();
		if (!g_shell.cpid)
		{
			close(fd_current[0]);
			dup2(*fd_prev, STDIN_FILENO);
			dup2(fd_current[1], STDOUT_FILENO);
			exec_conditionnal(cmd);
		}
		ft_append_elt(&pid_lst, (int *)&(g_shell.cpid));
		pid_lst = pid_lst->next;
		close(fd_current[1]);
		close(*fd_prev);
		*fd_prev = fd_current[0];
		cmd = cmd->next;
	}
}

void	ft_fst_pipe(t_cmd *cmd, int *fd_current, int *fd_prev, t_list *pid_lst)
{
	pipe(fd_current);
	g_shell.cpid = fork();
	if (!g_shell.cpid)
	{
		close(fd_current[0]);
		dup2(fd_current[1], STDOUT_FILENO);
		exec_conditionnal(cmd);
	}
	ft_append_elt(&pid_lst, (int *)&(g_shell.cpid));
	close(fd_current[1]);
	*fd_prev = fd_current[0];
}

void	ft_last_pipe(t_cmd *cmd, t_list *pid_lst, int *fd_current, int *fd_prev)
{
	g_shell.cpid = fork();
	if (!g_shell.cpid)
	{
		dup2(*fd_prev, STDIN_FILENO);
		exec_conditionnal(cmd);
	}
	close(fd_current[0]);
	while (pid_lst)
	{
		wait(pid_lst->data);
		pid_lst = pid_lst->next;
	}
}

int		ft_exec_pipe(t_cmd *cmd)
{
	int		fd_current[2];
	int		fd_prev;
	t_list	*pid_lst;
	t_list	*tmp;

	pid_lst = ft_calloc(sizeof(t_list), 1);
	ft_fst_pipe(cmd, fd_current, &fd_prev, pid_lst);
	cmd = cmd->next;
	pipe_loop(cmd, pid_lst, fd_current, &fd_prev);
	while (cmd->next)
	{
		cmd = cmd->next;
	}
	ft_last_pipe(cmd, pid_lst, fd_current, &fd_prev);
	wait(&g_shell.cpid);
	g_shell.status = WEXITSTATUS(g_shell.cpid);
	g_shell.cpid = 0;
	while (pid_lst)
	{
		tmp = pid_lst;
		pid_lst = pid_lst->next;
		free(tmp);
	}
	return (EXIT_SUCCESS);
}
