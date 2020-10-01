/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:07:55 by abarot            #+#    #+#             */
/*   Updated: 2020/10/01 10:22:11 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_delete(char *str, char *elt, unsigned int index)
{
	char	*res;
	int		i;

	i = 0;
	if (!str || !elt || index > ft_strlen(str) ||
		!(res = (char *)ft_calloc(1, ft_strlen(str) - ft_strlen(elt) + 1)))
		return (0);
	ft_memcpy(res, str, index);
	ft_memcpy(res + index, str + index + ft_strlen(elt),
			ft_strlen(str) - index - ft_strlen(elt));
	return (res);
}
