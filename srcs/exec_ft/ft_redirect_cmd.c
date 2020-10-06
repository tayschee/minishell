/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:00:15 by abarot            #+#    #+#             */
/*   Updated: 2020/10/07 16:31:23 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_declare(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
}

void	ft_set_cwd(void)
{
	g_shell.cwd = getcwd(g_shell.cwd, PATH_MAX);
	if (!(g_shell.r_cwd = ft_replace_in_str(g_shell.cwd, g_shell.tilde, "~")))
	{
		free(g_shell.r_cwd);
		g_shell.r_cwd = ft_strdup(getcwd(g_shell.cwd, PATH_MAX));
	}
	ft_append_elt(&g_garb_cltor, g_shell.r_cwd);
}

int		ft_redirect_cmd(t_cmd *cmd)
{
	g_shell.status = EXIT_SUCCESS;
	if (ft_issamestr(cmd->argv[0], "exit"))
		exit(EXIT_SUCCESS);
	else if (ft_issamestr(cmd->argv[0], "cd"))
		cd_cmd(cmd);
	else if (ft_issamestr(cmd->argv[0], "echo"))
		echo_cmd(cmd->argv);
	else if (ft_issamestr(cmd->argv[0], "pwd"))
		ft_putendl_fd(g_shell.cwd, 1);
	else if (ft_issamestr(cmd->argv[0], "export"))
		ft_export_cmd(cmd);
	else if (ft_issamestr(cmd->argv[0], "env_declare"))
		ft_env_declare(g_shell.envp);
	else if (ft_issamestr(cmd->argv[0], "unset"))
		ft_unset_cmd(cmd->argv);
	else if (ft_issamestr(cmd->argv[0], "env"))
		ft_show_tab(g_shell.envp);
	return (EXIT_SUCCESS);
}
