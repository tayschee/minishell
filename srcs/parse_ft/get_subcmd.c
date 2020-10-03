/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_subcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:13:04 by abarot            #+#    #+#             */
/*   Updated: 2020/10/03 15:27:27 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_get_cmd_end(char *cmd_line)
{
	if (!(ft_strchr(cmd_line, ';')))
		return (ft_strlen(cmd_line));
	else if (!(ft_count_elt(cmd_line, "\"") % 2) ||
			!(ft_count_elt(cmd_line, "\'") % 2))
		return (ft_strchr(cmd_line, ';') - cmd_line);
	else
		return (ft_strlen(cmd_line));
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
		if (cmd)
			ft_append_elt(&g_garb_cltor, cmd);
		if (!(cmd_struc = ft_init_cmd(cmd)))
			return (EXIT_FAILURE);
		ft_cmd_treatment(cmd_struc);
		cmd_end++;
		cmd_line += cmd_end;
		while (*cmd_line == ' ')
			cmd_line++;
	}
	return (EXIT_SUCCESS);
}
