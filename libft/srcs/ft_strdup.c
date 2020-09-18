/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:39:15 by abarot            #+#    #+#             */
/*   Updated: 2020/07/22 15:58:35 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	i = 0;
	if (!s ||
		!(dest = (char *)ft_calloc((ft_strlen((char *)s) + 1), sizeof(char))))
		return (0);
	while (*s)
	{
		dest[i] = *s;
		s++;
		i++;
	}
	return (dest);
}
