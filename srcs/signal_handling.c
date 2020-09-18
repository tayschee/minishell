/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:26:16 by abarot            #+#    #+#             */
/*   Updated: 2020/09/15 15:36:40 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_quithandler() 
{
	//quit signal à voir
	printf("\nQuit signal detected\n");
}

void ft_inthandler() 
{
	//interrup signal à voir
	if (g_shell.cpid)
		kill(g_shell.cpid, SIGTERM);
	else
	{
		write(1, "\n", 1);
		ft_show_prompt_line();
	}
}
