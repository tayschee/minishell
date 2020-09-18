/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 11:49:20 by abarot            #+#    #+#             */
/*   Updated: 2020/07/03 11:56:29 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_base(char *nbr, char *base)
{
	int	nb;
	int	len;

	nb = 0;
	len = strlen(base);
	while (*nbr)
	{
		nb = ft_strchr(base, *nbr) + (nb * len);
		nbr++;
	}
	return (nb);
}
