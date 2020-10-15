/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:12:53 by abarot            #+#    #+#             */
/*   Updated: 2020/10/15 15:11:21 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(char *paths, int instc)
{
	int		path_s;
	int		path_end;
	char	*path;
	char	*tmp;

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
	tmp = ft_substr(paths, path_s, path_end - path_s);
	path = ft_strjoin(tmp, "/");
	free(tmp);
	return (path);
}

int		ft_exec_paths(t_cmd *cmd)
{
	char	*path_inst;
	char	*first_cmd;
	int		instc;
	char	**argv_cp;

	instc = 0;
	first_cmd = ft_strdup(cmd->argv[0]);
	argv_cp = 0;
	if (!(argv_cp = ft_copy_tab(argv_cp, cmd->argv)))
		return (EXIT_FAILURE);
	if (execve(argv_cp[0], argv_cp, g_shell.envp) == -1)
	{
		while ((path_inst = ft_get_path(ft_get_env(g_shell.envp,
					"PATH", '='), instc)))
		{
			free(argv_cp[0]);
			argv_cp[0] = ft_strjoin(path_inst, first_cmd);
			free(path_inst);
			if (execve(argv_cp[0], argv_cp, g_shell.envp) == -1)
				instc++;
			else
			{
				ft_clear_tab(argv_cp);
				return (EXIT_SUCCESS);
			}
		}
		ft_clear_tab(argv_cp);
		return (127);
	}
	else
	{
		ft_clear_tab(argv_cp);
		return (EXIT_SUCCESS);

	}
}

int		ft_exec(t_cmd *cmd)
{
	g_shell.cpid = fork();
	if (!g_shell.cpid)
		exit(ft_exec_paths(cmd));
	waitpid(g_shell.cpid, &g_shell.status, 0);
	if (WEXITSTATUS(g_shell.status) == 127 && cmd->type == PATH)
	{
		ft_putstr_fd(cmd->argv[0], STDOUT_FILENO);
		ft_putstr_fd(": command not found\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	g_shell.cpid = 0;
	return (EXIT_SUCCESS);
}

int		ft_cmd_treatment(t_cmd *cmd)
{
	if (!cmd)
		return (EXIT_FAILURE);
	else if (cmd->next)
	{
		ft_exec_pipe(cmd);
		ft_append_env(g_shell.envp, "_=");
	}
	else if (cmd->rdr)
		ft_manage_rdr(cmd);
	else if (cmd->type == CMD)
		ft_redirect_cmd(cmd);
	else if (cmd->type == PATH)
		ft_exec(cmd);
	if (!cmd->next && (strcmp(cmd->argv[0], "export") || !cmd->argv[1]))
		change_env_(cmd);
	free_cmd_list(&cmd);
	return (EXIT_SUCCESS);
}
