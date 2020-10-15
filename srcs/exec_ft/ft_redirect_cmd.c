/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:00:15 by abarot            #+#    #+#             */
/*   Updated: 2020/10/15 16:09:43 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_declare(char **envp)
{
	int	i;
	int j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (envp[i][j] != '=')
			j++;
		write(STDOUT_FILENO, envp[i], j + 1);
		write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, &envp[i][j + 1], ft_strlen(&envp[i][j + 1]));
		write(STDOUT_FILENO, "\"\n", 2);
		i++;
	}
}

void	ft_create_env_declare(t_cmd *cmd)
{
	free(cmd->argv[0]);
	free(cmd->argv);
	if (!(cmd->argv = ft_calloc(2, sizeof(char *))) ||
		!(cmd->next = ft_calloc(1, sizeof(t_cmd))) ||
		!(cmd->next->argv = ft_calloc(2, sizeof(char *))))
		exit(EXIT_FAILURE);
	cmd->type = CMD;
	cmd->next->type = PATH;
	cmd->next->rdr = cmd->rdr;
	cmd->rdr = 0;
	cmd->argv[0] = ft_strdup("env_declare");
	cmd->argv[1] = 0;
	cmd->next->argv[0] = ft_strdup("sort");
	cmd->next->argv[1] = 0;
	cmd->next->next = 0;
	ft_exec_pipe(cmd);
}

void	ft_set_cwd(void)
{
	if (!(g_shell.cwd = ft_calloc(1, PATH_MAX)))
		return ;
	g_shell.cwd = getcwd(g_shell.cwd, PATH_MAX);
	if (!(g_shell.r_cwd = ft_replace_in_str(g_shell.cwd, g_shell.tilde, "~")))
	{
		g_shell.r_cwd = ft_strdup(g_shell.cwd);
	}
	ft_append_elt(&g_garb_cltor, g_shell.cwd);
	ft_append_elt(&g_garb_cltor, g_shell.r_cwd);
}

int		ft_redirect_cmd(t_cmd *cmd)
{
	g_shell.status = EXIT_SUCCESS;
	if (ft_issamestr(cmd->argv[0], "exit"))
		g_shell.exit = 1;
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
	{
		ft_append_env(g_shell.envp, "_=env");
		ft_show_tab(g_shell.envp);
	}
	return (EXIT_SUCCESS);
}
