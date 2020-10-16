/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_elt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:55:46 by abarot            #+#    #+#             */
/*   Updated: 2020/10/13 13:58:12 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_elt(char *str, char *elt)
{
	size_t count;

	count = 0;
	if (!str || !elt)
		return (0);
	while (*str && ft_strlen(str) >= ft_strlen(elt))
	{
		if (!ft_strncmp(str, elt, ft_strlen(elt)))
			count++;
		str++;
	}
	return (count);
}
