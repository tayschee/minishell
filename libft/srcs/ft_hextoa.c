/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:25:46 by abarot            #+#    #+#             */
/*   Updated: 2020/07/28 15:05:56 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_fill_hextoa(char *res, unsigned int n)
{
	char		*hexchar;

	hexchar = "0123456789abcdef";
	if (n > 16)
		ft_fill_hextoa(res, n / 16);
	res[ft_strlen(res)] = hexchar[(n % 16)];
}

char	*ft_hextoa(unsigned int n)
{
	char	*res;
	int		i;

	if (!(res = (char *)calloc(sizeof(char), 17)))
		return (0);
	ft_fill_hextoa(res, n);
	return (res);
}
