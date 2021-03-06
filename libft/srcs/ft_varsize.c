/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_varsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:05:36 by abarot            #+#    #+#             */
/*   Updated: 2020/10/01 11:50:01 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_varsize(char *var, char sep)
{
	int i;

	i = 0;
	while (var[i] && var[i] != sep)
		i++;
	if (!var[i])
		return (0);
	return (i);
}
