/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:54:40 by abarot            #+#    #+#             */
/*   Updated: 2020/10/20 12:59:39 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_oldpwd(void)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", g_shell.cwd);
	ft_append_env(g_shell.envp, tmp);
	ft_append_elt(&g_garb_cltor, tmp);
	ft_set_cwd();
	tmp = ft_strjoin("PWD=", g_shell.cwd);
	ft_append_env(g_shell.envp, tmp);
	ft_append_elt(&g_garb_cltor, tmp);
}

void	cd_cmd_error(t_cmd *cmd)
{
	ft_putstr_fd("minishell: cd: ", 1);
	ft_putstr_fd(cmd->argv[1], 1);
	ft_putendl_fd(": No such file or directory", 1);
	g_shell.status = EXIT_FAILURE;
}

void	cd_cmd_less(t_cmd *cmd)
{
	free(cmd->argv[1]);
	cmd->argv[1] = ft_strdup("..");
	cd_cmd(cmd);
	ft_putendl_fd(g_shell.cwd, 1);
}

void	cd_cmd(t_cmd *cmd)
{
	int		val;

	if (!cmd->argv[1])
	{
		if (chdir(ft_get_env(g_shell.envp, "HOME", '=')) == -1)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 1);
			g_shell.status = EXIT_FAILURE;
			return ;
		}
	}
	else if (cmd->argv[2])
	{
		if (cmd->argv[2])
			ft_putendl_fd("minishell: cd: too many arguments", 1);
		g_shell.status = EXIT_FAILURE;
	}
	else if (ft_issamestr(cmd->argv[1], "-"))
		cd_cmd_less(cmd);
	else if ((val = chdir(cmd->argv[1])) != -1)
		ft_create_oldpwd();
	else
		cd_cmd_error(cmd);
}
