/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_retreive_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:07:59 by abarot            #+#    #+#             */
/*   Updated: 2020/10/01 11:49:48 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_retreive_env(char **envp, char *str)
{
	int i;

	i = 0;
	while (envp[i] && ft_strncmp(str, envp[i],
			ft_max_value(ft_varsize(envp[i], '='),
			ft_varsize(str, '='))))
		i++;
	if (!ft_strncmp(str, envp[i], ft_strlen(str)))
	{
		while (envp[i + 1])
		{
			envp[i] = envp[i + 1];
			i++;
		}
		envp[i] = 0;
	}
}
