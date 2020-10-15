/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 15:11:25 by abarot            #+#    #+#             */
/*   Updated: 2020/10/15 15:11:33 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_copy_tab(char **cp, char **argv)
{
	int		i;

	i = 0;
	if (!(cp = ft_calloc(2, sizeof(argv))))
		return (0);
	while (argv[i])
	{
		cp[i] = ft_strdup(argv[i]);
		i++;
	}
	cp[i] = 0;
	return (cp);
}