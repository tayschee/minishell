/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_subcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:13:04 by abarot            #+#    #+#             */
/*   Updated: 2020/10/14 16:55:39 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_get_cmd_end(char *cmd_line)
{
	unsigned int	i;
	char			*coma_add;

	i = 0;
	while (cmd_line[i])
	{
		coma_add = ft_strchr(cmd_line + i, ';'); 
		if (!coma_add)
			return (ft_strlen(cmd_line));
		else if (!(ft_count_elt(coma_add, "\"") % 2) &&
			!(ft_count_elt(coma_add, "\'") % 2) && 
			*(coma_add - 1) != '\\')
			{
				i = coma_add - cmd_line;
				break ;
			}
		else
			i = coma_add - cmd_line + 1;
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
		cmd_line = cmd_line + cmd_end;
		if (*cmd_line)
			cmd_line++;
	}
	return (EXIT_SUCCESS);
}
