/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 15:15:17 by abarot            #+#    #+#             */
/*   Updated: 2020/09/15 16:01:11 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_create_cmdlist(char *cmd)
{
	t_list	*cmdlist;
	char	*elt;
	int		fd_in;
	int		fd_out;

	cmdlist = 0;
	elt = 0;
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	while (*cmd)
	{
		if (*cmd == '\"' || *cmd == '\'')
			elt = ft_get_string(cmd);
		else
			elt = ft_get_word(cmd);
		if (elt && *cmd != '<' && *cmd != '>')
			ft_append_elt(&cmdlist, elt);
		else if (elt)
			free(elt);
		if (*cmd == '\"' || *cmd == '\'')
			cmd += 2;
		else if (*cmd == '>' || *cmd == '<')
		{
			if (ft_redirection(cmd, &fd_in, &fd_out) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			break;
		}
		if (*cmd)
			cmd += ft_strlen(elt);
		while (*cmd == ' ')
			cmd++;
		if (!ft_strlen(elt))
			break;
	}
	if (ft_redirect_cmd(cmdlist, fd_in, fd_out) == EXIT_FAILURE)
	{
		ft_putstr_fd(cmdlist->data, 1);
		ft_putstr_fd(": command not found\n", 1);
		ft_clear_list(&cmdlist);
		return (EXIT_FAILURE);
	}
	ft_clear_list(&cmdlist);
	return (EXIT_SUCCESS);
}

int 	ft_parse_cmdline(char *cmd_line)
{
	char	*cmd;
	int		cmd_end;

	cmd_end = 0;
	if (!cmd_line)
		return (EXIT_SUCCESS);
	//subdivise_cmd(cmd_line);
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
		subdivise_cmd(cmd);
		ft_create_cmdlist(cmd);
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
			ft_count_elt(cmd_line, "\'") % 2 != 0)
	{
		ft_append_elt(&(g_garb_cltor), line);
		ft_putstr_fd("> ", 0);
		if (get_next_line(0, &line) == 0 && (ft_count_elt(line, "\"") % 2 != 1
				|| ft_count_elt(line, "\'") % 2 != 1))
			return ("\0");
		cmd_line = ft_insert(cmd_line, "\\n", ft_strlen(cmd_line));
		ft_append_elt(&(g_garb_cltor), cmd_line);
		cmd_line = ft_strjoin(cmd_line, line);
		ft_append_elt(&(g_garb_cltor), cmd_line);
	}
	return (cmd_line);
}
