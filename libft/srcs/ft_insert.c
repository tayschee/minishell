/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:37:01 by abarot            #+#    #+#             */
/*   Updated: 2020/09/14 14:28:10 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_insert(char *str, char *elt, unsigned int index)
{
	char	*res;	
	int i;

	i = 0;
	if (!str || !elt || index > ft_strlen(str) || 
		!(res = (char *)ft_calloc(1, ft_strlen(str) + ft_strlen(elt) + 1)))
		return (0);
	while (i != index)
	{
		res[i] = *str;
		i++;
		str++;
	}
	while (*elt)
	{
		res[i] = *elt;
		elt++;
		i++;
	}
	while (*str)
	{
		res[i] = *str;
		str++;
		i++;
	}
	return (res);
}
