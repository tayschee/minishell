/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_dollar_tilde.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 15:31:51 by tbigot            #+#    #+#             */
/*   Updated: 2020/10/15 16:10:52 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		end_of_tilde(char *txt)
{
	int	i;

	i = 0;
	while (txt[i] && txt[i] != ' ')
		i++;
	return(i);
}

int		bad_character_in_tilde(char *bad_c, char *in_tilde, char end)
{
	int 	i;
	int 	j;

	i = 0;
	while (in_tilde[i] && in_tilde[i] != end)
	{
		j = 0;
		while(bad_c[j])
		{
			if (in_tilde[i] == bad_c[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}