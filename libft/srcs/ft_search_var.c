/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:13:46 by abarot            #+#    #+#             */
/*   Updated: 2020/10/08 11:04:21 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_search_var(char **envp, char *str)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	if (*str == '{')
	{
		start++;
		end++;
	}
	while (envp[i] && ft_strncmp(envp[i], str + start,
			ft_varsize(envp[i], '=') - end))
		i++;
	if (*envp[i] == '_')
		i++;
	if (envp[i])
		return (ft_substr(str, start, ft_varsize(envp[i], '=')));
	return (0);
}
