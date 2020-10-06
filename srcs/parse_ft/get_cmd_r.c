/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:12:05 by abarot            #+#    #+#             */
/*   Updated: 2020/10/07 12:53:42 by abarot           ###   ########.fr       */
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

char	*ft_get_cmd_r(char *cmd_line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\\')
			i++;
		else if (ft_strnchr("$~", cmd_line[i], 2))
		{
			tmp = cmd_line;
			if (cmd_line[i] == '~' && !(ft_count_elt(cmd_line + i, "\'") % 2)
				&& !(ft_count_elt(cmd_line + i, "\"") % 2))
				cmd_line = ft_replace(cmd_line, "~", g_shell.tilde, i);
			else if (cmd_line[i] == '$' && !(ft_count_elt(cmd_line + i,
					"\'") % 2))
				cmd_line = ft_replace_var(cmd_line, cmd_line + i, i);
			else
				cmd_line = ft_strdup(cmd_line);
			free(tmp);
		}
		i++;
	}
	return (cmd_line);
}
