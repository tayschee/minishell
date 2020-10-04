/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:12:53 by abarot            #+#    #+#             */
/*   Updated: 2020/10/04 22:59:24 by abarot           ###   ########.fr       */
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

void	ft_wait_pidlst(t_list *head_lst)
{
	while (head_lst)
	{
		wait(head_lst->data);
		head_lst = head_lst->next;
	}
}

int		ft_exec_pipe(t_cmd *cmd)
{
	int		fd_current[2];
	int		fd_prev;
	t_list	*pid_lst;
	t_list	*head_lst;

	pid_lst = ft_calloc(sizeof(t_list), 1);
	head_lst = pid_lst;
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
	fd_prev = fd_current[0];
	cmd = cmd->next;
	pipe_loop(cmd, pid_lst, fd_current, &fd_prev);
	while (cmd->next)
	{
		cmd = cmd->next;
	}
	g_shell.cpid = fork();
	if (!g_shell.cpid)
	{
		dup2(fd_prev, STDIN_FILENO);
		exec_conditionnal(cmd);
	}
	close(fd_current[0]);
	ft_wait_pidlst(head_lst);
	wait(&g_shell.cpid);
	g_shell.status = WEXITSTATUS(g_shell.cpid);
	g_shell.cpid = 0;
	return (EXIT_SUCCESS);
}

int				ft_cmd_treatment(t_cmd *cmd)
{
	if (!cmd)
		return (EXIT_FAILURE);
	else if (!cmd->next && cmd->type == CMD)
	{
		if (cmd->rdr)
			ft_manage_rdr(cmd);
		else
			ft_redirect_cmd(cmd);
	}
	else if (!cmd->next && cmd->type == PATH)
		ft_exec(cmd);
	else
		ft_exec_pipe(cmd);
	if (g_shell.status && cmd->type == PATH)
	{
		ft_putstr_fd(cmd->argv[0], STDOUT_FILENO);
		ft_putstr_fd(": command not found\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
