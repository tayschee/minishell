/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_ft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:51:30 by abarot            #+#    #+#             */
/*   Updated: 2020/09/14 10:21:30 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_redirection(char *cmd, int *fd_in, int *fd_out)
{
	char	*file;

	if (*cmd == '>' && *(cmd + 1) == '>')
	{
		file = ft_get_word(cmd + 2);
		ft_append_elt(&g_garb_cltor, file);
		if ((*fd_out = open(file, O_RDWR | O_APPEND | O_CREAT, 0644)) == -1)
			return (EXIT_FAILURE);
	}
	else if (*cmd == '>')
	{
		file = ft_get_word(cmd + 1);
		ft_append_elt(&g_garb_cltor, file);
		if ((*fd_out = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644)) == -1)	
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(file, 1);
			ft_putstr_fd(": ", 1);
			ft_putendl_fd(strerror(errno), 1);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		file = ft_get_word(cmd + 1);
		ft_append_elt(&g_garb_cltor, file);
		if ((*fd_in = open(file, O_RDWR, 0644)) == -1)	
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}