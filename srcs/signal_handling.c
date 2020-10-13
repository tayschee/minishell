/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:26:16 by abarot            #+#    #+#             */
/*   Updated: 2020/10/13 11:29:26 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quithandler(void)
{
	if (g_shell.cpid)
	{
		kill(g_shell.cpid, SIGQUIT);
		g_shell.cpid = 0;
		write(1, "Quit (core dumped)\n", 19);
	}
}

void	ft_inthandler(void)
{
	if (g_shell.cpid)
	{
		kill(g_shell.cpid, SIGINT);
		g_shell.cpid = 0;
		write(1, "\n", 1);
	}
	else
	{
		//ajouter un free();de cmd_line
		write(1, "\n", 1);
		ft_show_prompt_line();
	}
}
