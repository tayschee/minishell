/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_word_no_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 13:20:02 by abarot            #+#    #+#             */
/*   Updated: 2020/10/14 15:59:00 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_word_no_quote(char *str)
{
	int	w_s;
	int	w_end;

	w_s = 0;
	w_end = 0;
	while (str[w_s] && (ft_isspace(str[w_s]) ||
			str[w_s] == '\"' || str[w_s] == '\''))
		w_s++;
	if (!str[w_s])
		return (0);
	w_end = w_s + 1;
	while (str[w_end] && !ft_isspace(str[w_end]) &&
			str[w_end] != '\"' && str[w_end] != '\'')
		w_end++;
	return (ft_substr(str, w_s, w_end));
}
