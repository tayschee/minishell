/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 17:03:57 by abarot            #+#    #+#             */
/*   Updated: 2020/10/02 11:01:38 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(char *paths, int instc)
{
	int		path_s;
	int		path_end;

	path_s = 0;
	while (paths[path_s] && instc)
	{
		if (paths[path_s] == ':')
			instc--;
		path_s++;
	}
	if (!paths[path_s])
		return (0);
	if (paths[path_s] == ':')
		path_s++;
	path_end = path_s + 1;
	while (paths[path_end] && paths[path_end] != ':')
		path_end++;
	return (ft_substr(paths, path_s, path_end - path_s));
}

void	ft_exec_paths(t_cmd *cmd)
{
	char	*path_inst;
	char	*path_str;
	char	*first_cmd;
	int		instc;

	instc = 0;
	first_cmd = ft_strdup(cmd->argv[0]);
	if (execve(cmd->argv[0], cmd->argv, g_shell.envp) == -1)
	{
		while ((path_inst = ft_get_path(ft_get_env(g_shell.envp,
					"PATH", '='), instc)))
		{
			path_str = ft_strjoin(path_inst, "/");
			path_str = ft_strjoin(path_str, first_cmd);
			cmd->argv[0] = path_str;
			if (execve(path_str, cmd->argv, g_shell.envp) == -1)
				instc++;
			else
				exit(EXIT_SUCCESS);
		}
		g_shell.l_rtrval = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}

int		ft_exec(t_cmd *cmd)
{
	if  (!cmd->next && cmd->type == CMD)
		ft_redirect_cmd(cmd);
	else
	{
		g_shell.cpid = fork();
		if (!g_shell.cpid)
		{
			//rdr_in_out(p_fd, p_fd[0], 0);
			cmd = fork_all(cmd);
			if (g_shell.cpid)
				wait(&g_shell.cpid);
			if (cmd->type == CMD)
			{
				ft_redirect_cmd(cmd);
				//free();
				exit(0);
			}
			else
				ft_exec_paths(cmd);
		}
		else
		{
			//rdr_in_out(p_fd, p_fd[1], 1);
			wait(&g_shell.cpid);
			g_shell.cpid = 0;
		}
	}
	if (g_shell.l_rtrval == EXIT_FAILURE)
	{
		ft_putstr_fd(cmd->argv[0], STDOUT_FILENO);
		ft_putstr_fd(": command not found\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
