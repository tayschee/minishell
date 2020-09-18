/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:04:20 by abarot            #+#    #+#             */
/*   Updated: 2020/04/21 17:14:13 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	if (size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	while (dst[i])
		i++;
	if ((i + 1) == size)
		return (ft_strlen(dst) + ft_strlen(src));
	while (src[j] && (i + j) <= (size - 2))
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	if (src[j])
		return (ft_strlen(src) + ft_strlen(dst) - j);
	return (ft_strlen(src) + ft_strlen(dst) - j);
}
