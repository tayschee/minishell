/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_ft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:23:28 by abarot            #+#    #+#             */
/*   Updated: 2020/09/19 15:35:47 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_restore_promptfd(int *p_fd, int *p_fd_save)
{
	if (p_fd[RD_END] > 2)
	{
		dup2(p_fd_save[RD_END], STDIN_FILENO);
		close(p_fd[RD_END]);
		close(p_fd_save[RD_END]);
	}
	if (p_fd[WR_END] > 2)
	{
		dup2(p_fd_save[WR_END], STDOUT_FILENO);
		close(p_fd[WR_END]);
		close(p_fd_save[WR_END]);
	}
}

void	ft_show_fileerr(char *file)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(file, 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd(strerror(errno), 1);
}

void	ft_get_fdrdr(t_rdr *rdr, int *p_fd)
{
	if (rdr && rdr->e_rdr == RDR_OUT)
		p_fd[WR_END] = open(rdr->path, O_RDWR | O_TRUNC | O_CREAT, 0644);
	else if (rdr && rdr->e_rdr == RDR_OUT_APPEND)
		p_fd[WR_END] = open(rdr->path, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (rdr && rdr->e_rdr == RDR_IN)
		p_fd[RD_END] = open(rdr->path, O_RDWR, 0644);
}
	
int		ft_redirection(t_rdr *rdr, int *p_fd)
{
	while (rdr)
	{
		if (p_fd[WR_END] && (rdr->e_rdr == RDR_OUT || 
								rdr->e_rdr == RDR_OUT_APPEND))
		{
			write(p_fd[WR_END], "", 1);
			close(p_fd[WR_END]);
		}
		else if (p_fd[RD_END] && rdr->e_rdr == RDR_IN)
			close(p_fd[RD_END]);
		ft_get_fdrdr(rdr, p_fd);
		if (p_fd[WR_END] == -1 || p_fd[RD_END] == -1)
		{
			ft_show_fileerr(rdr->path);
			return (EXIT_FAILURE);
		}
		rdr = rdr->next;
	}
	return (EXIT_SUCCESS);
}

int		ft_manage_rdr(t_cmd *cmd)
{
	int	p_fd[2];
	int p_fd_save[2];

	p_fd_save[RD_END] = dup(STDIN_FILENO);
	p_fd_save[WR_END] = dup(STDOUT_FILENO);
	p_fd[RD_END] = 0;
	p_fd[WR_END] = 0;
	if (cmd->rdr)
		if (ft_redirection(cmd->rdr, p_fd) == EXIT_FAILURE)
		{
			close(p_fd_save[RD_END]);
			close(p_fd_save[WR_END]);
			return (EXIT_FAILURE);
		}
	if (p_fd[RD_END] != 0)
		dup2(p_fd[RD_END], STDIN_FILENO);
	if (p_fd[WR_END] != 0)
		dup2(p_fd[WR_END], STDOUT_FILENO);
	if (cmd->type == PATH)
		ft_exec(cmd);
	else if (cmd->type == CMD)
		ft_redirect_cmd(cmd);
	ft_restore_promptfd(p_fd, p_fd_save);
	if (g_shell.l_rtrval == EXIT_FAILURE)
	{
		ft_putstr_fd(cmd->argv[0], STDOUT_FILENO);
		ft_putstr_fd(": command not found\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
