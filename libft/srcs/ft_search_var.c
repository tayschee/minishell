/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:13:46 by abarot            #+#    #+#             */
/*   Updated: 2020/10/01 11:49:57 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_search_var(char **envp, char *str)
{
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], str, ft_varsize(envp[i], '=')))
		i++;
	if (envp[i])
		return (ft_substr(str, 0, ft_varsize(envp[i], '=')));
	return (0);
}
