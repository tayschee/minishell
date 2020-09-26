/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 15:15:17 by abarot            #+#    #+#             */
/*   Updated: 2020/09/26 12:35:10 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	ft_parse_cmdline(char *cmd_line)
{
	char	*cmd;
	int		cmd_end;
	t_cmd	*cmd_struc;

	cmd_end = 0;
	if (!cmd_line)
		return (EXIT_SUCCESS);
	while (*cmd_line)
	{
		while (!cmd_end)
		{
			if (!(ft_strchr(cmd_line, ';')))
				cmd_end = ft_strlen(cmd_line);
			else if (!(ft_count_elt(cmd_line + cmd_end, "\"") % 2) ||
					!(ft_count_elt(cmd_line + cmd_end, "\'") % 2))
				cmd_end = ft_strchr(cmd_line, ';') - cmd_line;
			else
				cmd_end = ft_strlen(cmd_line);
		}
		cmd = ft_substr(cmd_line, 0, cmd_end);
		if (cmd)
			ft_append_elt(&g_garb_cltor, cmd);
		cmd_struc = ft_init_cmd(cmd);
		if (ft_cmd_treatment(cmd_struc) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		cmd_end++;
		cmd_line += cmd_end;
		while (*cmd_line == ' ')
			cmd_line++;
		cmd_end = 0;
	}
	return (EXIT_SUCCESS);
}

char	*ft_replace_var(char *res, char *cmd_line)
{
	char	*var;
	char	*var_dol;

	var = ft_search_var(g_shell.envp, cmd_line + 1);
	if (var)
	{
		var_dol = ft_strjoin("$", var);
		res = ft_replace_in_str(res, var_dol, 
			ft_get_value(g_shell.envp, var, '='));
	}
	else
		return (res);
	ft_append_elt(&(g_garb_cltor), res);
	free(var);
	free(var_dol);
	return (res);
}

char	*ft_get_cmd_r(char *cmd_line)
{
	char	*res;

	res = cmd_line;
	// ---- ajouter $? treatment ----
	if (*cmd_line == '$' && *(cmd_line + 1) == '?')
		cmd_line++;
	//-------------------------------
	else if (*cmd_line == '$' && !(ft_count_elt(cmd_line, "\'") % 2))
		res = ft_replace_var(res, cmd_line);
	cmd_line++;
	while (*cmd_line)
	{
		if (*cmd_line == '\\')
			cmd_line++;
		else if (*cmd_line == '~' && !(ft_count_elt(cmd_line, "\'") % 2) 
				&& !(ft_count_elt(cmd_line, "\"") % 2))
			res = ft_replace_in_str(res, "~", g_shell.tilde);
		else if (*cmd_line == '$' && !(ft_count_elt(cmd_line, "\'") % 2))
			res = ft_replace_var(res, cmd_line);
		cmd_line++;
	}
	return (res);
}

char	*ft_multiline_mng(char *line)
{
	char	*cmd_line;

	cmd_line = line;
	while (ft_count_elt(cmd_line, "\"") % 2 != 0 || 
			ft_count_elt(cmd_line, "\'") % 2 != 0 ||
			(ft_strchr(line, '\\') && *(ft_strchr(line, '\\') + 1) == '\0'))
	{
		ft_append_elt(&(g_garb_cltor), cmd_line);
		if (ft_strchr(line, '\\') && *(ft_strchr(line, '\\') + 1) == '\0')
		{
			cmd_line = ft_delete(line, "\\", ft_strlen(line) - 1);
			ft_append_elt(&(g_garb_cltor), cmd_line);
		}
		ft_putstr_fd("> ", 0);
		if (get_next_line(0, &line) == 0 && (ft_count_elt(line, "\"") % 2 != 1
				|| ft_count_elt(line, "\'") % 2 != 1 || 
			(ft_strchr(line, '\\') && *(ft_strchr(line, '\\') + 1) != '\0')))
			return ("\0");
		if (ft_count_elt(cmd_line, "\"") % 2 != 0 || ft_count_elt(cmd_line, "\'") % 2 != 0)
		{
			cmd_line = ft_insert(cmd_line, "\\n", ft_strlen(cmd_line));
			ft_append_elt(&(g_garb_cltor), cmd_line);
		}
		cmd_line = ft_strjoin(cmd_line, line);
		ft_append_elt(&(g_garb_cltor), cmd_line);
	}
	return (cmd_line);
}
