/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 17:03:57 by abarot            #+#    #+#             */
/*   Updated: 2020/10/08 17:24:24 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_loop(t_cmd *cmd, t_pipe *pinfo, int *fd_current, int *fd_prev)
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
		ft_append_pipe_struc(pinfo, g_shell.cpid, cmd->argv[0]);
		close(fd_current[1]);
		close(*fd_prev);
		*fd_prev = fd_current[0];
		cmd = cmd->next;
	}
}

void	ft_fst_pipe(t_cmd *cmd, int *fd_current, int *fd_prev, t_pipe *pinfo)
{
	pipe(fd_current);
	g_shell.cpid = fork();
	if (!g_shell.cpid)
	{
		close(fd_current[0]);
		dup2(fd_current[1], STDOUT_FILENO);
		exec_conditionnal(cmd);
	}
	close(fd_current[1]);
	*fd_prev = fd_current[0];
	pinfo->pid = g_shell.cpid;
	pinfo->cmd = cmd->argv[0];
	pinfo->next = 0;
}

void	ft_last_pipe(t_cmd *cmd, t_pipe *pinfo, int *fd_current, int *fd_prev)
{
	g_shell.cpid = fork();
	if (!g_shell.cpid)
	{
		dup2(*fd_prev, STDIN_FILENO);
		exec_conditionnal(cmd);
	}
	close(fd_current[0]);
	ft_append_pipe_struc(pinfo, g_shell.cpid, cmd->argv[0]);
	while (pinfo)
	{
		waitpid(pinfo->pid, &pinfo->status, 0);
		pinfo = pinfo->next;
	}
}

void	ft_check_and_free_pinfo(t_pipe *pipe_info)
{
	t_pipe	*tmp;

	while (pipe_info)
	{
		if (WEXITSTATUS(pipe_info->status) == 127)
		{
			ft_putstr_fd(pipe_info->cmd, STDOUT_FILENO);
			ft_putstr_fd(": command not found\n", STDOUT_FILENO);
		}
		tmp = pipe_info;
		pipe_info = pipe_info->next;
		free(tmp);
	}
}

int		ft_exec_pipe(t_cmd *cmd)
{
	int		fd_current[2];
	int		fd_prev;
	t_pipe	*pipe_info;

	if (!(pipe_info = ft_calloc(sizeof(t_pipe), 1)))
		return (EXIT_FAILURE);
	ft_fst_pipe(cmd, fd_current, &fd_prev, pipe_info);
	cmd = cmd->next;
	pipe_loop(cmd, pipe_info, fd_current, &fd_prev);
	while (cmd->next)
	{
		cmd = cmd->next;
	}
	ft_last_pipe(cmd, pipe_info, fd_current, &fd_prev);
	ft_check_and_free_pinfo(pipe_info);
	g_shell.cpid = 0;
	return (EXIT_SUCCESS);
}
