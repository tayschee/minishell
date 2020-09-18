/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:28:02 by abarot            #+#    #+#             */
/*   Updated: 2020/01/20 11:28:10 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_toupper_string(char *str)
{
	int i_str;

	i_str = 0;
	if (!str)
		return (0);
	while (str[i_str])
	{
		str[i_str] = ft_toupper(str[i_str]);
		i_str++;
	}
	return (str);
}
