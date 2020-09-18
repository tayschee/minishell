/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addtoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:25:08 by abarot            #+#    #+#             */
/*   Updated: 2020/07/28 15:03:12 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_fill_addtoa(char *res, unsigned long n)
{
	char		*hexchar;

	hexchar = "0123456789abcdef";
	if (n >= 16)
		ft_fill_addtoa(res, n / 16);
	res[ft_strlen(res)] = hexchar[(n % 16)];
}

char		*ft_addtoa(unsigned long n)
{
	char	*res;
	int		i;

	if (!(res = (char*)calloc(sizeof(char), 17)))
		return (0);
	ft_fill_addtoa(res, n);
	res = ft_strjoin(ft_strdup("0x\0"), res);
	return (res);
}
