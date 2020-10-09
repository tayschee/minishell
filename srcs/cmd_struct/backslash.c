/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:08:21 by abarot            #+#    #+#             */
/*   Updated: 2020/10/09 11:51:34 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void		ft_retreive_bs_in_cmd(t_cmd *cmd)
{
	int		i;

	while (cmd)
	{
		i = -1;
		while (cmd->argv[++i])
			cmd->argv[i] = cmd_without_bs(cmd->argv[i]);
		cmd = cmd->next;
	}
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

void		bs_loop(char *cmd_no_bs, char *cmd, int i, int bs)
{
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
	bs_loop(cmd_no_bs, cmd, i, bs);
	free(cmd);
	return (cmd_no_bs);
}
