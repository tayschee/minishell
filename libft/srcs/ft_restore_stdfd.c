/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restore_stdfd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 12:01:04 by abarot            #+#    #+#             */
/*   Updated: 2020/10/02 11:48:44 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_restore_stdfd(int *p_fd, int *saved_fd)
{
	if (p_fd[RD_END])
	{
		dup2(saved_fd[RD_END], STDIN_FILENO);
		close(p_fd[RD_END]);
		close(saved_fd[RD_END]);
	}
	if (p_fd[WR_END])
	{
		dup2(saved_fd[WR_END], STDOUT_FILENO);
		close(p_fd[WR_END]);
		close(saved_fd[WR_END]);
	}
}
