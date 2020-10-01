/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_stdfd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 12:14:07 by abarot            #+#    #+#             */
/*   Updated: 2020/10/01 12:15:23 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_init_stdfd(int *n_fd, int *saved_fd)
{
	saved_fd[RD_END] = dup(STDIN_FILENO);
	saved_fd[WR_END] = dup(STDOUT_FILENO);
	n_fd[RD_END] = 0;
	n_fd[WR_END] = 0;
}
