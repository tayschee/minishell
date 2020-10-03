/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:12:05 by abarot            #+#    #+#             */
/*   Updated: 2020/10/03 15:42:00 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_replace_statusvar(char *res, int index)
{
	char	*var;

	var = ft_itoa(g_shell.status);
	res = ft_replace(res, "$?", var, index);
	free(var);
	return (res);
}

char	*ft_replace_var(char *res, char *cmd_line, int index)
{
	char	*var;
	char	*var_dol;

	if (*(cmd_line + 1) == '?')
		return (ft_replace_statusvar(res, index));
	var = ft_search_var(g_shell.envp, cmd_line + 1);
	if (var)
	{
		var_dol = ft_strjoin("$", var);
		res = ft_replace(res, var_dol,
			ft_get_env(g_shell.envp, var, '='), index);
	}
	else
	{
		var = ft_get_word(cmd_line + 1);
		var_dol = ft_strjoin("$", var);
		res = ft_replace(res, var_dol, "", index);
	}
	free(var);
	free(var_dol);
	return (res);
}

char	*ft_get_cmd_r(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			ft_append_elt(&g_garb_cltor, line);
			line = ft_delete(line, "\\", i);
		}
		else if (ft_strchr("$~", line[i]))
		{
			ft_append_elt(&g_garb_cltor, line);
			if (line[i] == '~' && !(ft_count_elt(line + i, "\'") % 2)
				&& !(ft_count_elt(line + i, "\"") % 2))
				line = ft_replace(line, "~", g_shell.tilde, i);
			else if (line[i] == '$' && !(ft_count_elt(line + i, "\'") % 2))
				line = ft_replace_var(line, line + i, i);
			else
				line = ft_strdup(line);
		}
		i++;
	}
	return (line);
}
