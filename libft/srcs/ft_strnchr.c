/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:37:39 by abarot            #+#    #+#             */
/*   Updated: 2020/09/29 15:55:43 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *s, int c, unsigned int n)
{
	if (!s)
		return (0);
	if (!c)
		return ((char *)s);
	while (*s && n)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
		n--;
	}
	return (0);
}
