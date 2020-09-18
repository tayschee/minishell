/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:19:14 by abarot            #+#    #+#             */
/*   Updated: 2020/07/28 15:05:52 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_fill_itoa(char *res, int n)
{
	if (n > 10)
		ft_fill_itoa(res, n / 10);
	res[ft_strlen(res)] = (n % 10) + '0';
}

char		*ft_itoa(int n)
{
	char		*res;

	if (!n)
		return (ft_char_to_str('0'));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!(res = (char *)ft_calloc(sizeof(char), 12)))
		return (0);
	if (n < 0)
	{
		*res = '-';
		n = -n;
		ft_fill_itoa(res + 1, n);
	}
	else
		ft_fill_itoa(res, n);
	return (res);
}
