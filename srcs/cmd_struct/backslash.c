/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:08:21 by abarot            #+#    #+#             */
/*   Updated: 2020/10/07 18:13:39 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char		*backslash_for_string(char *str)
{
	int		i;
	int		bs;
	char	*str_with_bs;

	i = -1;
	bs = 0;
	while (str[++i])
	{
		if (str[i] == '\\')
			bs++;
	}
	if (bs == 0)
		return (str);
	if (!(str_with_bs = ft_calloc(sizeof(char), i + bs + 1)))
		return (NULL);
	i = -1;
	bs = 0;
	while (str[++i])
	{
		str_with_bs[bs++] = str[i];
		if (str[i] == '\\')
			str_with_bs[bs++] = '\\';
	}
	free(str);
	return (str_with_bs);
}

int			skip_bs(char *cmd, char *new_cmd)
{
	int		i;

	i = 0;
	while (cmd[i] == '\\')
	{
		if (new_cmd)
			new_cmd[i] = cmd[i];
		i++;
		if (cmd[i])
		{
			if (new_cmd)
				new_cmd[i] = cmd[i];
			i++;
		}
	}
	return (i);
}

static int	how_many_bs(char *cmd)
{
	int		i;
	int		bs;

	i = -1;
	bs = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\\')
		{
			if (cmd[i + 1] == '\\')
				i++;
			bs++;
		}
	}
	return (bs);
}

char		*cmd_without_bs(char *cmd)
{
	int		i;
	int		bs;
	char	*cmd_no_bs;

	i = 0;
	if ((bs = how_many_bs(cmd)) == 0)
		return (cmd);
	while (cmd[i])
		i++;
	if (!(cmd_no_bs = ft_calloc(sizeof(char), (i - bs + 1))))
		return (NULL);
	i = -1;
	bs = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\\')
		{
			i++;
		}
		cmd_no_bs[bs] = cmd[i];
		if (!cmd[i])
			break ;
		bs++;
	}
	free(cmd);
	return (cmd_no_bs);
}
