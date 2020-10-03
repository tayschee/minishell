/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline_mng.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:11:24 by abarot            #+#    #+#             */
/*   Updated: 2020/10/03 15:49:17 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_inside_str(char *line)
{
	if (ft_count_elt(line, "\"") % 2 ||
		ft_count_elt(line, "\'") % 2)
		return (1);
	return (0);
}

char	*ft_multiline_mng(char *line)
{
	char	*cmd_line;

	cmd_line = line;
	while (ft_is_inside_str(cmd_line) ||
			(ft_strchr(line, '\\') && *(ft_strchr(line, '\\') + 1) == '\0'))
	{
		ft_append_elt(&(g_garb_cltor), cmd_line);
		if (ft_strchr(line, '\\') && *(ft_strchr(line, '\\') + 1) == '\0')
		{
			cmd_line = ft_delete(cmd_line, "\\", ft_strlen(cmd_line) - 1);
			ft_append_elt(&(g_garb_cltor), cmd_line);
		}
		ft_putstr_fd("> ", 0);
		if (get_next_line(0, &line) == 0 && (!ft_is_inside_str(line) ||
			(ft_strchr(line, '\\') && *(ft_strchr(line, '\\') + 1) != '\0')))
			return ("\0");
		if (ft_is_inside_str(cmd_line))
		{
			cmd_line = ft_insert(cmd_line, "\\n", ft_strlen(cmd_line));
			ft_append_elt(&(g_garb_cltor), cmd_line);
		}
		cmd_line = ft_strjoin(cmd_line, line);
	}
	ft_append_elt(&(g_garb_cltor), cmd_line);
	return (cmd_line);
}
