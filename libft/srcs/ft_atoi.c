/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:37:03 by abarot            #+#    #+#             */
/*   Updated: 2020/09/03 14:11:26 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_get_sign(const char *s, int *sign)
{
	while (*s && !ft_isdigit(*s))
	{
		if (!ft_isspace(*s) || *s != '-' || *s != '+')
			return (0);
		if ((*s == '-' && !ft_isdigit(*(s + 1))) ||
		(*s == '+' && !ft_isdigit(*(s + 1))))
			return (0);
		else if (*s == '-')
			*sign = -1;
		s++;
	}
	return (1);
}

int		ft_atoi(const char *s)
{
	int sign;
	int nbr;

	sign = 1;
	nbr = 0;
	if (!s || !(ft_get_sign(s, &sign)))
		return (0);
	while (!ft_isdigit(*s))
		s++;
	while (*s >= '0' && *s <= '9')
	{
		nbr = nbr * 10 + (*s - 48);
		s++;
	}
	return (sign * nbr);
}
