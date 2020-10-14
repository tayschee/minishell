/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:50:53 by abarot            #+#    #+#             */
/*   Updated: 2020/10/14 11:43:11 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace(char *old_str, char *to_rpl, char *elt, int index)
{
	char	*n_str;

	if (!old_str || !to_rpl || !elt || !(n_str = ft_calloc(ft_strlen(old_str)
		+ ft_strlen(elt) - ft_strlen(to_rpl) + 1, 2)))
		return (0);
	ft_memcpy(n_str, old_str, index);
	ft_memcpy(n_str + index, elt, ft_strlen(elt));
	ft_memcpy(n_str + index + ft_strlen(elt), old_str + index +
	ft_strlen(to_rpl), ft_strlen(old_str) - index - ft_strlen(to_rpl));
	return (n_str);
}
