/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:12:05 by abarot            #+#    #+#             */
/*   Updated: 2020/10/16 19:14:45 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_replace_brackets_(char *res, char *var, int index)
{
	char	*var_dol;
	char	*tmp;

	var_dol = ft_strjoin("${", var);
	tmp = var_dol;
	var_dol = ft_strjoin(var_dol, "}");
	free(tmp);
	res = ft_replace(res, var_dol,
		ft_get_env(g_shell.envp, var, '='), index);
	free(var_dol);
	return (res);
}

char	*ft_replace_brackets(char *res, int index)
{
	char	*tmp;
	char	*var;
	char	*var_dol;
	int		end;

	end = index + 2;
	while (res[end] && res[end] != '}')
		end++;
	tmp = ft_substr(res, index + 2, end - index - 2);
	var = ft_search_var(g_shell.envp, tmp);
	if (!var)
	{
		var = ft_strjoin("${", tmp);
		var_dol = ft_strjoin(var, "}");
		res = ft_replace(res, var_dol, "", index);
		free(var_dol);
	}
	else
		res = ft_replace_brackets_(res, var, index);
	free(tmp);
	free(var);
	return (res);
}
