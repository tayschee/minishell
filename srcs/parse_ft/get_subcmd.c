/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_subcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:13:04 by abarot            #+#    #+#             */
/*   Updated: 2020/10/13 15:47:46 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_get_cmd_end(char *cmd_line)
{
	int		i;
	char	c;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == ';')
			return (i);
		i += skip_bs(&cmd_line[i], NULL);
		while (cmd_line[i] && ((c = cmd_line[i]) == '"' || c == '\''))
		{
			i++;
			if (cmd_line[i] == '\\' && c == '"')
			{
				i++;
				if (cmd_line[i])
					i++;
			}
			if (c == cmd_line[i])
				c = 0;
		}
		if (cmd_line[i])
			i++;
	}
	return (i);
}

int		ft_get_subcmd(char *cmd_line)
{
	char	*cmd;
	int		cmd_end;
	t_cmd	*cmd_struc;

	if (!cmd_line)
		return (EXIT_SUCCESS);
	while (*cmd_line)
	{
		cmd_end = ft_get_cmd_end(cmd_line);
		cmd = ft_substr(cmd_line, 0, cmd_end);
		if (!(cmd_struc = ft_init_cmd(cmd)))
			return (EXIT_FAILURE);
		ft_cmd_treatment(cmd_struc);
		cmd_line += cmd_end;
		if (*cmd_line == ';')
			cmd_line++;
	}
	return (EXIT_SUCCESS);
}
