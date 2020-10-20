/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_ft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:30:20 by abarot            #+#    #+#             */
/*   Updated: 2020/10/20 11:47:52 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_syntax_error_disp(char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 1);
	write(1, &c, 1);
	(c == ';') ? write(1, &c, 1) : 0;
	ft_putstr_fd("'\n", 1);
}

int		syntax(char *cmd_line, char c)
{
	int		i;

	while (*cmd_line)
	{
		i = 0;
		while (*(cmd_line + i) && (*(cmd_line + i) != c ||
			(*(cmd_line + i) == c && ((ft_count_elt(cmd_line + i, "\"") % 2) ||
			(ft_count_elt(cmd_line + i, "\'") % 2) ||
			(i && *(cmd_line + i - 1) == '\\')))))
			i++;
		if (!*(cmd_line + i))
			return (1);
		*(cmd_line + i) = '\0';
		if (ft_count_elt(cmd_line, " ") == ft_strlen(cmd_line))
		{
			*(cmd_line + i) = c;
			ft_syntax_error_disp(c);
			return (0);
		}
		*(cmd_line + i) = c;
		cmd_line += i + 1;
	}
	return (1);
}
