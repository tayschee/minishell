/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 14:10:25 by abarot            #+#    #+#             */
/*   Updated: 2020/10/20 15:23:26 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cmd_with_split_word(char *cmd, char *op, int j)
{
	int		i;
	char	*new_cmd;

	if (!(new_cmd = ft_calloc(j * 2, sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		j += skip_bs(&cmd[i], &new_cmd[j]);
		i += skip_bs(&cmd[i], NULL);
		if (cmd[i] && ft_strchr(op, cmd[i]))
		{
			new_cmd[j++] = ' ';
			new_cmd[j++] = cmd[i++];
			if (cmd[i - 1] == cmd[i])
				new_cmd[j++] = cmd[i++];
			new_cmd[j++] = ' ';
		}
		else if (cmd[i])
			new_cmd[j++] = cmd[i++];
	}
	return (new_cmd);
}

static char	*split_word(char *cmd, char *operator)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		i += skip_bs(&cmd[i], NULL);
		if (cmd[i] && ft_strchr(operator, cmd[i]))
		{
			j += 2;
			if (cmd[i + 1] == cmd[i])
				i++;
		}
		if (cmd[i])
			i++;
	}
	return (cmd_with_split_word(cmd, operator, j + i));
}

static int	check_error_rdr(char **cmd, int end)
{
	int		i;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			if (this_is_operator(cmd[i], RDR_LIST) >= 0
			&& (!cmd[i + 1] || this_is_operator(cmd[i + 1],
			OPERATOR_LIST) > 0))
			{
				print_msg_error(end);
				return (EXIT_FAILURE);
			}
			if (!ft_strncmp(cmd[i], "|", 2) && (i == 0 ||
			this_is_operator(cmd[i - 1], OPERATOR_LIST) > 0))
			{
				print_msg_error(end);
				return (EXIT_FAILURE);
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

t_cmd		*ft_init_cmd(char *unique_cmd)
{
	char	*cmd_sentence;
	char	**cmd_divise;
	t_cmd	*cmd;

	cmd = NULL;
	cmd_sentence = split_word(unique_cmd, "<>|");
	if (unique_cmd)
		free(unique_cmd);
	cmd_divise = ft_get_argv(cmd_sentence);
	if (cmd_sentence)
		free(cmd_sentence);
	if (check_error_rdr(cmd_divise, g_end_of_cmd) == EXIT_SUCCESS)
		cmd = char_to_struct_cmd(cmd_divise);
	else
		ft_clear_tab(cmd_divise);
	ft_retreive_bs_in_cmd(cmd);
	return (cmd);
}
