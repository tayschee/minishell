/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 14:55:25 by abarot            #+#    #+#             */
/*   Updated: 2020/10/20 12:55:00 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_cmd(char **argv)
{
	int i;

	i = 0;
	if (argv[1])
	{
		while (argv[i + 1])
		{
			ft_retreive_env(g_shell.envp, argv[i + 1]);
			i++;
		}
	}
}

void	ft_manage_cmd_clone(char *argv)
{
	int		j;
	char	*tmp;
	char	*cmd_clone;

	j = 0;
	while (argv[j] && argv[j] != '=')
		j++;
	tmp = ft_substr(argv, 0, j);
	cmd_clone = ft_strjoin("_=", tmp);
	if (tmp)
		free(tmp);
	ft_append_env(g_shell.envp, cmd_clone);
	ft_append_elt(&g_garb_cltor, cmd_clone);
}

void	ft_export_cmd(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!cmd->argv[1])
		ft_create_env_declare(cmd);
	else
	{
		i = 1;
		while (cmd->argv[i])
		{
			if (verif_export_word(cmd->argv[i]))
			{
				tmp = ft_strdup(cmd->argv[i]);
				ft_append_env(g_shell.envp, tmp);
				ft_append_elt(&g_garb_cltor, tmp);
				ft_manage_cmd_clone(cmd->argv[i]);
			}
			i++;
		}
	}
}
