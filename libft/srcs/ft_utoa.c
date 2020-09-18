/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:28:24 by abarot            #+#    #+#             */
/*   Updated: 2020/01/20 11:29:09 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_utoa(unsigned int n)
{
	char			*res;
	int				i;

	res = (char*)malloc(sizeof(char) * 12);
	if (res == 0)
		return (0);
	i = 0;
	if (n == 0)
		res[i++] = 48;
	if (n > 4294967295)
		n = 4294967295;
	while (n >= 1)
	{
		res[i] = (n % 10) + 48;
		n = n / 10;
		i++;
	}
	res[i] = '\0';
	return (ft_reverse_string(res));
}
