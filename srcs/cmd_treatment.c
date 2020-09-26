/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:12:53 by abarot            #+#    #+#             */
/*   Updated: 2020/09/26 09:43:10 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cmd_treatment(t_cmd *cmd)
{
	if (cmd->rdr)
		ft_manage_rdr(cmd);
	else if (cmd->next)
	{
		printf("\nthere is a pipe\n");
		ft_cmd_treatment(cmd->next);
	}
	else if (cmd->type == CMD)
		ft_redirect_cmd(cmd);
	else if (cmd->type == PATH)
		ft_exec(cmd);
	free_cmd_list(&cmd);
	return (EXIT_SUCCESS);
}
