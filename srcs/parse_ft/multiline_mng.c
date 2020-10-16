/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline_mng.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:11:24 by abarot            #+#    #+#             */
/*   Updated: 2020/10/16 14:50:40 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_multiline_cmd(char *cmd_line, char *line)
{
	char	*tmp;

	if (!g_shell.in_multil)
	{
		free(cmd_line);
		cmd_line = ft_strjoin(line, "");
		free(line);
	}
	else
	{
		tmp = line;
		line = ft_strjoin("\n", line);
		free(tmp);
		tmp = cmd_line;
		cmd_line = ft_strjoin(cmd_line, line);
		free(tmp);
		free(line);
	}
	return (cmd_line);
}

char	*ft_multiline_mng(char *line)
{
	char	*cmd_line;
	char	c;
	char	*tmp;

	cmd_line = line;
	while ((c = quote_management(cmd_line)))
	{
		g_shell.in_multil = 1;
		if (c == '\\')
		{
			tmp = cmd_line;
			cmd_line = ft_delete(cmd_line, "\\", ft_strlen(cmd_line) - 1);
			free(tmp);
		}
		ft_putstr_fd("> ", STDOUT_FILENO);
		if (!get_next_line(STDOUT_FILENO, &line))
		{
			ft_putendl_fd(UN_EOF, STDOUT_FILENO);
			free(line);
			free(cmd_line);
			return (0);
		}
		cmd_line = ft_join_multiline_cmd(cmd_line, line);
	}
	return (cmd_line);
}
