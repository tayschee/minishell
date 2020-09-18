/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 14:36:26 by abarot            #+#    #+#             */
/*   Updated: 2020/08/31 16:43:35 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clear_list(t_list **list)
{
	t_list	*tmp;

	while ((*list)->next)
	{
		tmp = *list;
		free((*list)->data);
		*list = (*list)->next;
		free(tmp);
	}
	free((*list)->data);
	free(*list);
	*list = 0;
}
