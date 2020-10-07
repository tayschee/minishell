/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:10:38 by abarot            #+#    #+#             */
/*   Updated: 2020/10/07 16:44:03 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_append_env(char **envp, char *str)
{
	int i;

	i = 0;
	if (!ft_strchr(str, '='))
		return ;
	while (envp[i] && ft_strncmp(str, envp[i],
			ft_max_value(ft_varsize(envp[i], '='), ft_varsize(str, '='))))
		i++;
	if (!envp[i])
	{
		envp[i] = ft_strdup(str);
		envp[i + 1] = 0;
	}
	else
		envp[i] = ft_strdup(str);
}
