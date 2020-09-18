/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:53:03 by abarot            #+#    #+#             */
/*   Updated: 2020/07/03 11:50:26 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*s_end;
	char		*d_end;

	if (!dest || !src)
		return (0);
	d_end = (char *)dest + (n - 1);
	s_end = (char *)src + (n - 1);
	if (dest < src)
		while (n)
		{
			*(char *)dest = *(char *)src;
			dest++;
			src++;
			n--;
		}
	else
		while (n)
		{
			*(char *)d_end = *(char *)s_end;
			dest--;
			src--;
			n--;
		}
	return (dest);
}
