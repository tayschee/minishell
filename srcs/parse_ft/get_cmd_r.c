/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:12:05 by abarot            #+#    #+#             */
/*   Updated: 2020/10/19 17:36:17 by abarot           ###   ########.fr       */
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
	if (*(cmd_line + 1) == '{')
		return (ft_replace_brackets(res, index));
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
		res = ft_delete(res, var_dol, index);
	}
	free(var);
	free(var_dol);
	return (res);
}

char	*ft_if_dollar_or_tilde(char *cmd_line, int i)
{
	char	*tmp;

	if (!ft_strncmp(cmd_line + i, "${", 2) && (*(cmd_line + i + 2) == 0 ||
	ft_strchr("}~^&()+=[]%%\"'\\|.,><:; ", *(cmd_line + i + 2)) ||
	!bad_character_in_tilde("${&*()[];' \"\\|<>.", cmd_line + i + 2, '}')))
	{
		write(2, "minishell: ${", 13);
		write(2, cmd_line + i + 2, end_of_tilde(cmd_line + i + 2));
		ft_putendl_fd(": bad substitution", 2);
		free(cmd_line);
		return (0);
	}
	tmp = cmd_line;
	if (cmd_line[i] == '~' && !(ft_count_elt(cmd_line + i, "\"") % 2))
		cmd_line = ft_replace(cmd_line, "~", g_shell.tilde, i);
	else if (cmd_line[i] == '$')
		cmd_line = ft_replace_var(cmd_line, cmd_line + i, i);
	else
		cmd_line = ft_strdup(cmd_line);
	free(tmp);
	return (cmd_line);
}

void	skip_squote(char *cmd, int *i)
{
	if (cmd[*i] == '\'' && !(*i && cmd[*i - 1] == '\\') &&
	!(ft_count_elt(cmd + *i, "\"") % 2))
	{
		*i = *i + 1;
		while (cmd[*i] && (cmd[*i] != '\'' || (*i && cmd[*i - 1] == '\\')))
			*i = *i + 1;
	}
}

char	*ft_get_cmd_r(char *cmd)
{
	int		i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		i += skip_bs(&cmd[i], NULL);
		skip_squote(cmd, &i);
		if (cmd[i] == '~' || (cmd[i] == '$' && (cmd[i + 1] != ' ' &&
		cmd[i + 1] != '\0' && cmd[i + 1] != '\"')))
		{
			if (!(cmd = ft_if_dollar_or_tilde(cmd, i)))
				return (0);
			if (cmd[i] == '~')
				i++;
		}
		else
			i++;
	}
	return (cmd);
}
