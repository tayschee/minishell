/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 12:32:58 by abarot            #+#    #+#             */
/*   Updated: 2020/07/29 12:35:18 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_list_size(t_list *list)
{
	int i;

	if (!list)
		return (0);
	i = 1;
	while (list->next)
	{
		i++;
		list = list->next;
	}
	return (i);
}
