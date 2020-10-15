/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_in_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:50:53 by abarot            #+#    #+#             */
/*   Updated: 2020/10/15 15:57:44 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace_in_str(char *o_str, char *to_replace, char *elt)
{
	char	*n_str;
	int		i_nstr;

	i_nstr = 0;
	if (!o_str || !to_replace || !elt || !(n_str = ft_calloc(ft_strlen(o_str) +
		(ft_count_elt(o_str, to_replace) * ft_strlen(elt) + 1), 1)))
		return (0);
	while (*o_str)
	{
		while (*o_str && ft_strncmp(o_str, to_replace, ft_strlen(to_replace)))
		{
			n_str[i_nstr] = *o_str;
			o_str++;
			i_nstr++;
		}
		if (*o_str)
		{
			ft_strlcpy(n_str + i_nstr, elt, ft_strlen(elt));
			o_str = o_str + ft_strlen(to_replace);
			i_nstr += ft_strlen(elt);
		}
	}
	return (n_str);
}
