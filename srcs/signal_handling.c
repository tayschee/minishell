/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:26:16 by abarot            #+#    #+#             */
/*   Updated: 2020/10/20 06:42:59 by abarot           ###   ########.fr       */
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
	else
		write(1, "\b\b  \b\b", 6);
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
