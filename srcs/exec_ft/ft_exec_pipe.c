/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 17:03:57 by abarot            #+#    #+#             */
/*   Updated: 2020/10/07 17:50:28 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_append_pipe_struc(t_pipe *pipe, pid_t pid, char *cmd)
{
	t_pipe	*n_pipe;

	if (!(n_pipe = ft_calloc(1, sizeof(t_pipe))))
		return (EXIT_FAILURE);
	n_pipe->pid = pid;
	n_pipe->cmd = cmd;
	n_pipe->next = 0;
	while (pipe->next)
		pipe = pipe->next;
	pipe->next = n_pipe;
	return (EXIT_SUCCESS);
}

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
		wait(&(pinfo->pid));
		pinfo = pinfo->next;
	}
}

int		ft_exec_pipe(t_cmd *cmd)
{
	int		fd_current[2];
	int		fd_prev;
	t_pipe	*pipe_info;
	t_pipe	*tmp;

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
	while (pipe_info)
	{
		if (WEXITSTATUS(pipe_info->pid) == 127)
		{
			g_shell.status = WEXITSTATUS(pipe_info->pid);
			ft_putstr_fd(pipe_info->cmd, STDOUT_FILENO);
			ft_putstr_fd(": command not found\n", STDOUT_FILENO);
		}
		tmp = pipe_info;
		pipe_info = pipe_info->next;
		free(tmp);
	}
	g_shell.cpid = 0;
	return (EXIT_SUCCESS);
}
