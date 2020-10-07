/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 14:10:25 by abarot            #+#    #+#             */
/*   Updated: 2020/10/07 10:42:54 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cmd_with_split_word(char *cmd, char *operator, int j)
{
	int		i;
	char	*new_cmd;

	if (!(new_cmd = ft_calloc(j + 1, sizeof(char))))
		return (NULL);
	i = -1;
	j = 0;
	while (cmd[++i])
	{
		if (ft_strchr(operator, cmd[i]))
		{
			if (i == 0 || ((cmd[i - 1] != ' ' && cmd[i - 1] != 92)
			&& (cmd[i] != cmd[i - 1] || (i >= 2 && cmd[i - 2] == '\\'))))
				new_cmd[j++] = ' ';
			new_cmd[j] = cmd[i];
			if ((i == 0 || cmd[i - 1] != '\\') &&
			(cmd[i + 1] != cmd[i] && cmd[i + 1] != ' '))
				new_cmd[++j] = ' ';
		}
		else
			new_cmd[j] = cmd[i];
		j++;
	}
	return (new_cmd);
}

static char	*split_word(char *cmd, char *operator)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (ft_strchr(operator, cmd[i]))
		{
			if (i == 0 || ((cmd[i - 1] != ' ' && cmd[i - 1] != '\\') &&
			(cmd[i] != cmd[i - 1] || (i >= 2 && cmd[i - 2] == '\\'))))
				j++;
			if ((i == 0 || cmd[i - 1] == '\\')
			&& (cmd[i + 1] != cmd[i] && cmd[i + 1] != ' '))
				j++;
		}
		j++;
		i++;
	}
	return (cmd_with_split_word(cmd, operator, j));
}

static int	check_error_rdr(char **cmd)
{
	int i;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			if (this_is_operator(cmd[i], RDR_LIST) >= 0
			&& (!cmd[i + 1] || this_is_operator(cmd[i + 1],
			OPERATOR_LIST) > 0))
			{
				write(1, UNEXP_NL, ft_strlen(UNEXP_NL));
				return (EXIT_FAILURE);
			}
			if (!ft_strncmp(cmd[i], "|", 2) && (i == 0 ||
			this_is_operator(cmd[i - 1], OPERATOR_LIST) > 0))
			{
				write(1, UNEXP_NL, ft_strlen(UNEXP_NL));
				return (EXIT_FAILURE);
			}
			i++;
		}
	}
	return (-1);
}

char		**ft_get_argv(char *cmd)
{
	char	**argv;
	int		i;

	i = 0;
	if (!(argv = ft_calloc(ft_count_elt(cmd, " ") + 2, sizeof(char *))))
		return (0);
	while (*cmd)
	{
		if (*cmd == '\"' || *cmd == '\'')
		{
			argv[i] = ft_get_string(cmd);
			argv[i] = backslash_for_string(argv[i]);
			cmd += 2;
		}
		else
			argv[i] = ft_get_word(cmd);
		cmd += ft_strlen(argv[i]);
		while (*cmd == ' ')
			cmd++;
		i++;
	}
	return (argv);
}

t_cmd		*ft_init_cmd(char *unique_cmd)
{
	t_cmd	*save;
	char	*cmd_sentence;
	char	**cmd_divise;
	t_cmd	*cmd;
	int		i;

	cmd = NULL;
	cmd_sentence = split_word(unique_cmd, "<>|");
	if (unique_cmd)
		free(unique_cmd);
	cmd_divise = ft_get_argv(cmd_sentence);
	if (cmd_sentence)
		free(cmd_sentence);
	if (check_error_rdr(cmd_divise) < 0)
		cmd = char_to_struct_cmd(cmd_divise);
	save = cmd;
	while (cmd)
	{
		i = -1;
		while (cmd->argv[++i])
			cmd->argv[i] = cmd_without_bs(cmd->argv[i]);
		cmd = cmd->next;
	}
	cmd = save;
	return (cmd);
}
