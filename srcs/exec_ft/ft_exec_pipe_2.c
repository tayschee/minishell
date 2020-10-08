/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:09:12 by abarot            #+#    #+#             */
/*   Updated: 2020/10/08 17:22:03 by abarot           ###   ########.fr       */
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
	n_pipe->status = 0;
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
