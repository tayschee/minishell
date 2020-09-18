/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:35:26 by abarot            #+#    #+#             */
/*   Updated: 2020/09/09 11:51:00 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checktrim(char c, char const *set)
{
	int k;

	k = 0;
	while (set[k])
	{
		if (set[k] == c)
			return (1);
		k++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		begin;
	int		end;

	if (!s1 || !set)
		return (0);
	begin = 0;
	end = ft_strlen(s1) - 1;
	while (ft_checktrim(s1[begin], set) == 1)
		begin++;
	if ((begin - 1) == end)
	{
		res = malloc(1);
		res[0] = 0;
		return (res);
	}
	while (ft_checktrim(s1[end], set) == 1)
		end--;
	res = ft_substr(s1, begin, (end - begin + 1));
	return (res);
}
