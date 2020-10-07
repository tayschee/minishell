/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:37:35 by abarot            #+#    #+#             */
/*   Updated: 2020/10/07 12:45:27 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_argv_str_and_char(char **cmd, char **argv, int i)
{
	char	*tmp;
	char	*argv_tmp;

	tmp = argv[i];
	if (**cmd == '\"' || **cmd == '\'')
	{
		argv_tmp = ft_get_string(*cmd);
		argv_tmp = backslash_for_string(argv_tmp);
		*cmd = *cmd + 2;
	}
	else
	{
		argv_tmp = ft_get_word_no_quote(*cmd);
	}
	argv[i] = ft_strjoin(argv[i], argv_tmp);
	*cmd = *cmd + ft_strlen(argv_tmp);
	free(tmp);
	free(argv_tmp);
}

void		ft_argv_str_or_char(char **cmd, char **argv, int i)
{
	if (**cmd != '\"' || **cmd != '\'')
		argv[i] = ft_get_word_no_quote(*cmd);
	else
	{
		argv[i] = ft_get_string(*cmd);
		argv[i] = backslash_for_string(argv[i]);
		*cmd = *cmd + 2;
	}
	*cmd = *cmd + ft_strlen(argv[i]);
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
		while (*cmd && *cmd != ' ')
		{
			if (argv[i])
				ft_argv_str_and_char(&cmd, argv, i);
			else
				ft_argv_str_or_char(&cmd, argv, i);
		}
		while (*cmd == ' ')
			cmd++;
		i++;
	}
	return (argv);
}
