/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:34:49 by abarot            #+#    #+#             */
/*   Updated: 2020/10/20 13:37:33 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_error_127(t_cmd *cmd)
{
	ft_putstr_fd(cmd->argv[0], STDOUT_FILENO);
	ft_putstr_fd(": command not found\n", STDOUT_FILENO);
	return (EXIT_FAILURE);
}

int		ft_error_128(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(cmd->argv[0], STDOUT_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
	g_shell.status = 127;
	return (EXIT_FAILURE);
}

int		ft_error_129(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(cmd->argv[0], STDOUT_FILENO);
	ft_putstr_fd(": Permission denied\n", STDOUT_FILENO);
	g_shell.status = 127;
	return (EXIT_FAILURE);
}
