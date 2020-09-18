/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_in_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:50:53 by abarot            #+#    #+#             */
/*   Updated: 2020/09/09 18:16:19 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace_in_str(char *old_str, char *to_replace, char *elt)
{
	char	*n_str;
	int		i_nstr;

	i_nstr = 0;
	if (!old_str || !to_replace || !elt || !(n_str = ft_calloc(ft_strlen(old_str) + 
		(ft_count_elt(old_str, to_replace) * ft_strlen(elt)), 1)))
		return (0);
	while (*old_str)
	{
		while (*old_str && ft_strncmp(old_str, to_replace, ft_strlen(to_replace)))
		{
			n_str[i_nstr] = *old_str;
			old_str++;
			i_nstr++;
		}
		if (*old_str)
		{
			ft_strlcpy(n_str + i_nstr, elt, ft_strlen(elt));
			old_str = old_str + ft_strlen(to_replace);
			i_nstr += ft_strlen(elt);
		}
	}
	return (n_str);
}
