/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:55:13 by abarot            #+#    #+#             */
/*   Updated: 2020/10/01 10:56:38 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_env(char **envp, char *var, char sep)
{
	int i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], var,
						ft_max_value(ft_varsize(envp[i], '='),
						ft_varsize(var, '='))))
		i++;
	if (ft_strchr(envp[i], sep))
		return (ft_strchr(envp[i], sep) + 1);
	return (0);
}
