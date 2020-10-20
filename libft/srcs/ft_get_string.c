/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 11:27:26 by abarot            #+#    #+#             */
/*   Updated: 2020/10/20 12:26:50 by abarot           ###   ########.fr       */
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
		str_s = str[str_s] == '\\' ? str_s + 2 : str_s + 1;
	if (!str[str_s])
		return (0);
	else if (str[str_s + 1] == str[str_s])
		return (ft_strdup(""));
	str_end = str_s + 1;
	while (str[str_end] && str[str_end] != str[str_s])
		str_end = str[str_end] == '\\' && str[str_s] != '\'' ?
		str_end + 2 : str_end + 1;
	if (!str[str_end])
		return (ft_substr(str, str_s, ft_strlen(str) - str_s));
	return (ft_substr(str, str_s + 1, (str_end - str_s - 1)));
}
