/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_stdfd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 12:24:34 by abarot            #+#    #+#             */
/*   Updated: 2020/10/01 12:29:49 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_replace_stdfd(int *n_fd)
{
	if (n_fd[RD_END])
		dup2(n_fd[RD_END], STDIN_FILENO);
	if (n_fd[WR_END])
		dup2(n_fd[WR_END], STDOUT_FILENO);
}
