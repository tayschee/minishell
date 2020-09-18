/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_elt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 14:37:12 by abarot            #+#    #+#             */
/*   Updated: 2020/08/28 12:10:56 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_append_elt(t_list **list, void *elt)
{
	t_list	*new_elt;
	t_list	*head;

	head = *list;
	if (!list || !elt || !(new_elt = malloc(sizeof(t_list))))
		return (EXIT_FAILURE);
	new_elt->data = elt;
	new_elt->next = 0;
	if (!(*list))
	{
		(*list) = new_elt;
		return (EXIT_SUCCESS);
	}
	while (head->next)
		head = head->next;
	head->next = new_elt;
	return (EXIT_SUCCESS);
}
