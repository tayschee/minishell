/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:37:35 by abarot            #+#    #+#             */
/*   Updated: 2020/10/16 18:49:20 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_argv_str_and_char(char **cmd, char **argv, int i)
{
	char	*tmp;
	char	*argv_tmp;

	tmp = argv[i];
	if (**cmd != '\"' && **cmd != '\'')
		argv_tmp = ft_get_word_no_quote(*cmd);
	else
	{
		argv_tmp = ft_get_string(*cmd);
		if (**cmd == '\'' && argv_tmp[0] != '\0')
		{
			tmp = argv_tmp;
			argv_tmp = ft_replace_in_str(argv_tmp, "\\", "\\\\");
			*cmd = *cmd + 2 - (ft_count_elt(argv_tmp, "\\") / 2);
			free(tmp);
		}
		else
			*cmd = *cmd + 2;
	}
	tmp = argv[i];
	argv[i] = ft_strjoin(argv[i], argv_tmp);
	*cmd = *cmd + ft_strlen(argv_tmp);
	free(tmp);
	free(argv_tmp);
}

void			ft_argv_str_or_char(char **cmd, char **argv, int i)
{
	char	*tmp;

	if (**cmd != '\"' && **cmd != '\'')
		argv[i] = ft_get_word_no_quote(*cmd);
	else
	{
		argv[i] = ft_get_string(*cmd);
		if (**cmd == '\'' && argv[i][0] != '\0')
		{
			tmp = argv[i];
			argv[i] = ft_replace_in_str(argv[i], "\\", "\\\\");
			*cmd = *cmd + 2 - (ft_count_elt(argv[i], "\\") / 2);
			free(tmp);
		}
		else
			*cmd = *cmd + 2;
	}
	*cmd = *cmd + ft_strlen(argv[i]);
}

char			**ft_get_argv(char *cmd)
{
	char	**argv;
	int		i;

	i = 0;
	if (!(argv = ft_calloc(ft_count_elt(cmd, " ") + 2, sizeof(char *))))
		return (0);
	while (*cmd)
	{
		while (*cmd == ' ')
			cmd++;
		while (*cmd && *cmd != ' ')
		{
			if (argv[i])
				ft_argv_str_and_char(&cmd, argv, i);
			else
				ft_argv_str_or_char(&cmd, argv, i);
		}
		i++;
	}
	return (argv);
}
