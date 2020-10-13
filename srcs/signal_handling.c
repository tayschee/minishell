/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:26:16 by abarot            #+#    #+#             */
/*   Updated: 2020/10/13 15:47:47 by tbigot           ###   ########.fr       */
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
		if (g_shell.in_multil == 1)
		{
			g_shell.in_multil = 0;
		}
		write(1, "\n", 1);
		ft_show_prompt_line();
	}
}
