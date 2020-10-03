/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:12:53 by abarot            #+#    #+#             */
/*   Updated: 2020/10/03 22:58:47 by abarot           ###   ########.fr       */
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
			exit (ft_manage_rdr(cmd));
		else
			exit (ft_exec_paths(cmd));
	}
}

int		ft_exec_pipe(t_cmd *cmd)
{
	int		fd[2];
	int		fd_save[2];

	fd_save[0] = dup(STDIN_FILENO);
	fd_save[1] = dup(STDOUT_FILENO);
	while (cmd->next)
	{
		pipe(fd);
		g_shell.cpid = fork();
		if (!g_shell.cpid)
		{
			close(fd[0]);
        	close(STDOUT_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			exec_conditionnal(cmd);
		}
		wait(&g_shell.cpid);
		close(fd[1]);
        close(STDIN_FILENO);
		dup2(fd[0], STDIN_FILENO);
		cmd = cmd->next;
	}
	g_shell.cpid = fork();
	if (!g_shell.cpid)
		exec_conditionnal(cmd);
	else
	{
		dup2(fd_save[0], STDIN_FILENO);
		dup2(fd_save[1], STDOUT_FILENO);
		close(fd_save[0]);
		close(fd_save[1]);
		wait(&g_shell.cpid);
		g_shell.status = WEXITSTATUS(g_shell.cpid);
		g_shell.cpid = 0;
	}
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
