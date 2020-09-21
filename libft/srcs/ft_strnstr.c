/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:57:36 by abarot            #+#    #+#             */
/*   Updated: 2020/09/21 11:39:01 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_check_tofind(const char *str, const char *to_find)
{
	int i;

	i = 0;
	while (to_find[i])
	{
		if (str[i] != to_find[i])
			return (0);
		i++;
	}
	return (1);
}

char		*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	unsigned int i_str;
	unsigned int to_return;

	i_str = 0;
	to_return = 0;
	if (!str || !to_find)
		return (0);
	if (!ft_strlen(to_find))
		return ((char *)str);
	while (i_str < n && str[i_str])
	{
		to_return = i_str;
		if (ft_check_tofind((str + to_return), to_find)
		&& (n - to_return) >= ft_strlen(to_find))
			return ((char *)(str + to_return));
		i_str++;
	}
	return (0);
}
