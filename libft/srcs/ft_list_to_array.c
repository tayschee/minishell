/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 12:29:26 by abarot            #+#    #+#             */
/*   Updated: 2020/10/01 10:23:51 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_list_to_array(t_list *list)
{
	void	**res;
	int		i;

	i = 0;
	if (!(res = malloc(ft_list_size(list) * sizeof(void *))))
		return (0);
	while (list)
	{
		res[i] = list->data;
		i++;
		list = list->next;
	}
	return (res);
}
