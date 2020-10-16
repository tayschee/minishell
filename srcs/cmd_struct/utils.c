/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 14:46:13 by abarot            #+#    #+#             */
/*   Updated: 2020/10/16 19:07:42 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			this_is_operator(char *cmd, char *operator)
{
	int		i;
	int		n;
	int		j;

	i = 0;
	j = -1;
	while (operator[i])
	{
		n = 0;
		while (operator[i + n] && operator[i + n] != ' ')
			n++;
		j++;
		if (!ft_strncmp(cmd, &operator[i], n))
			return (i);
		i += n;
		if (operator[i])
			i++;
	}
	return (-1);
}

int			count_struct(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int			path_or_cmd(char *argv)
{
	if (ft_issamestr(argv, "exit") || ft_issamestr(argv, "cd") ||
		ft_issamestr(argv, "echo") || ft_issamestr(argv, "pwd") ||
		ft_issamestr(argv, "export") || ft_issamestr(argv, "unset") ||
		ft_issamestr(argv, "env"))
		return (CMD);
	return (PATH);
}

char		quote_management(char *txt)
{
	char	c;
	int		i;

	i = 0;
	c = 0;
	while (txt[i])
	{
		c = txt[i];
		if (c == '\\')
			i++;
		while ((c == '"' || c == '\'') && txt[++i])
		{
			if (c == '"' && txt[i] == '\\')
				i++;
			else if (txt[i] == c)
				break ;
		}
		if (txt[i])
		{
			c = 0;
			i++;
		}
	}
	return (c);
}

void		print_msg_error(int end)
{
	write(1, UNEXP_NL, ft_strlen(UNEXP_NL));
	if (end == 1)
		write(1, ";'\n", 3);
	else if (end == 2)
		write(1, ";;'\n", 4);
	else
		write(1, "newline'\n", 10);
}
