/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:02:44 by abarot            #+#    #+#             */
/*   Updated: 2020/10/12 16:36:18 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	int		end;

	end = 0;
	if (!s || !(dest = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	if (start > ft_strlen(s))
	{
		dest[0] = '\0';
		return (dest);
	}
	while (((len - end) > 0) && s[start + end])
	{
		dest[end] = s[start + end];
		end++;
	}
	dest[end] = '\0';
	return (dest);
}
