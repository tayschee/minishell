/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_ft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:23:28 by abarot            #+#    #+#             */
/*   Updated: 2020/10/13 15:36:11 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_show_fileerr(char *file)
{
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(file, STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_putendl_fd(strerror(errno), STDOUT_FILENO);
}

void	ft_get_fdrdr(t_rdr *rdr, int *fd)
{
	if (rdr && rdr->e_rdr == RDR_OUT)
		fd[WR_END] = open(rdr->path, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (rdr && rdr->e_rdr == RDR_OUT_APPEND)
		fd[WR_END] = open(rdr->path, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (rdr && rdr->e_rdr == RDR_IN)
		fd[RD_END] = open(rdr->path, O_RDWR, 0644);
}

int		ft_redirection(t_rdr *rdr, int *fd, int *feed)
{
	while (rdr)
	{
		if (fd[WR_END] && (rdr->e_rdr == RDR_OUT ||
				rdr->e_rdr == RDR_OUT_APPEND))
			close(fd[WR_END]);
		else if (fd[RD_END] && rdr->e_rdr == RDR_IN)
		{
			close(fd[RD_END]);
			*feed = 0;
		}
		else if (rdr->e_rdr == RDR_IN_FEED)
		{
			*feed = 1;
			if (fd[RD_END])
				close(fd[RD_END]);
		}
		ft_get_fdrdr(rdr, fd);
		if (fd[WR_END] == -1 || fd[RD_END] == -1)
		{
			ft_show_fileerr(rdr->path);
			return (EXIT_FAILURE);
		}
		rdr = rdr->next;
	}
	return (EXIT_SUCCESS);
}

void	ft_feed(t_cmd *cmd, int *fd, int *fd_save, int *p_fd)
{
	char	*line;

	pipe(p_fd);
	write(STDOUT_FILENO, "> ", 2);
	while (get_next_line(STDIN_FILENO, &line) == 1)
	{
		if (!ft_issamestr(line, cmd->rdr->path))
		{
			ft_putendl_fd(line, p_fd[WR_END]);
			free(line);
			write(STDOUT_FILENO, "> ", 2);
		}
		else
			break ;
	}
	close(p_fd[WR_END]);
	dup2(p_fd[RD_END], STDIN_FILENO);
	if (fd[WR_END])
		dup2(fd[WR_END], STDOUT_FILENO);
	if (cmd->type == CMD)
		ft_redirect_cmd(cmd);
	else
		ft_exec(cmd);
	dup2(fd_save[RD_END], STDIN_FILENO);
	close(p_fd[RD_END]);
}

int		ft_manage_rdr(t_cmd *cmd)
{
	int		fd[3];
	int		fd_save[3];
	int		feed;
	int		p_fd[2];

	feed = 0;
	ft_init_stdfd(fd, fd_save);
	if (ft_redirection(cmd->rdr, fd, &feed) == EXIT_FAILURE)
	{
		close(fd_save[RD_END]);
		close(fd_save[WR_END]);
		return (EXIT_FAILURE);
	}
	if (feed)
		ft_feed(cmd, fd, fd_save, p_fd);
	else
	{
		ft_replace_stdfd(fd);
		if (cmd->type == CMD)
			ft_redirect_cmd(cmd);
		else
			ft_exec(cmd);
	}
	ft_restore_stdfd(fd, fd_save);
	return (EXIT_SUCCESS);
}
