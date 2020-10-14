/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:12:05 by abarot            #+#    #+#             */
/*   Updated: 2020/10/14 13:53:15 by abarot           ###   ########.fr       */
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

char	*ft_replace_brackets(char *res, char *var, int index)
{
	char	*tmp;
	char	*var_dol;

	var_dol = ft_strjoin("${", var);
	tmp = var_dol;
	var_dol = ft_strjoin(var_dol, "}");
	free(tmp);
	res = ft_replace(res, var_dol,
		ft_get_env(g_shell.envp, var, '='), index);
	free(var_dol);
	return (res);
}

char	*ft_replace_var(char *res, char *cmd_line, int index)
{
	char	*var;
	char	*var_dol;

	if (*(cmd_line + 1) == '?')
		return (ft_replace_statusvar(res, index));
	var = ft_search_var(g_shell.envp, cmd_line + 1);
	if (*(cmd_line + 1) == '{' && var)
		return (ft_replace_brackets(res, var, index));
	else if (var)
	{
		var_dol = ft_strjoin("$", var);
		res = ft_replace(res, var_dol,
			ft_get_env(g_shell.envp, var, '='), index);
	}
	else
	{
		var = ft_get_word(cmd_line + 1);
		var_dol = ft_strjoin("$", var);
		res = ft_delete(res, var_dol, index);
	}
	free(var);
	free(var_dol);
	return (res);
}

char	*ft_if_dollar_or_tilde(char *cmd_line, int i)
{
	char	*tmp;

	if (!ft_strncmp(cmd_line + i, "${", 2) && 
		ft_strchr("[]()$", *(cmd_line + i + 2)))
	{
		free(cmd_line);
		ft_putendl_fd("minishell: ${}: bad substitution", STDOUT_FILENO);
		return (0);
	}
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
	return (cmd_line);
}

char	*ft_get_cmd_r(char *cmd_line)
{
	int		i;

	i = 0;
	if (!cmd_line)
		return (0);
	while (cmd_line[i])
	{
		i += skip_bs(&cmd_line[i], NULL);
		if (ft_strnchr("$~", cmd_line[i], 2) && cmd_line[i + 1])
		{
			if (!(cmd_line = ft_if_dollar_or_tilde(cmd_line, i)))
				return (0);
		}
		else
			i++;
	}
	return (cmd_line);
}
