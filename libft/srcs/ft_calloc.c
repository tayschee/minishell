/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:22:59 by abarot            #+#    #+#             */
/*   Updated: 2020/04/20 20:59:37 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void *dest;

	if (!(num * size))
	{
		num = 1;
		size = 1;
	}
	if (!(dest = malloc(num * size)))
		return (0);
	ft_bzero(dest, (size * num));
	return (dest);
}
