/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_ft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:23:28 by abarot            #+#    #+#             */
/*   Updated: 2020/10/02 11:46:46 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (rdr && rdr->e_rdr == RDR_OUT_APPEND)
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
			close(p_fd[WR_END]);
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
