/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 11:27:26 by abarot            #+#    #+#             */
/*   Updated: 2020/10/01 10:20:52 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_string(char *str)
{
	int	str_s;
	int	str_end;

	str_s = 0;
	str_end = 0;
	if (!str)
		return (0);
	while (str[str_s] && str[str_s] != '\"' && str[str_s] != '\'')
		str_s++;
	if (!str[str_s])
		return (0);
	str_end = str_s + 1;
	while (str[str_end] && str[str_end] != str[str_s])
		str_end++;
	if (!str[str_end])
		return (0);
	return (ft_substr(str, str_s + 1, (str_end - str_s - 1)));
}
