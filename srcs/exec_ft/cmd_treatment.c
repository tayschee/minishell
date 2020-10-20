/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:12:53 by abarot            #+#    #+#             */
/*   Updated: 2020/10/20 13:40:45 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_rtr_exec(char **argv, int rtr_val)
{
	ft_clear_tab(argv);
	return (rtr_val);
}

int		ft_try_paths(char **argv_cp)
{
	char	*path_inst;
	int		instc;
	char	*first_cmd;

	instc = 0;
	first_cmd = ft_strdup(argv_cp[0]);
	while ((path_inst = ft_get_path(ft_get_env(g_shell.envp,
				"PATH", '='), instc)))
	{
		free(argv_cp[0]);
		argv_cp[0] = ft_strjoin(path_inst, first_cmd);
		free(path_inst);
		if (execve(argv_cp[0], argv_cp, g_shell.envp) != -1)
		{
			free(first_cmd);
			return (ft_rtr_exec(argv_cp, EXIT_SUCCESS));
		}
		instc++;
	}
	free(first_cmd);
	return (ft_rtr_exec(argv_cp, 127));
}

int		ft_exec_paths(t_cmd *cmd)
{
	char		**argv_cp;
	struct stat	tmp;

	argv_cp = 0;
	if (!(argv_cp = ft_copy_tab(argv_cp, cmd->argv)))
		return (EXIT_FAILURE);
	if (ft_is_a_path(argv_cp[0]))
	{
		if (execve(argv_cp[0], argv_cp, g_shell.envp) == -1)
		{
			if (stat(argv_cp[0], &tmp) == 0)
				return (ft_rtr_exec(argv_cp, 129));
			else
				return (ft_rtr_exec(argv_cp, 128));
		}
		else
			return (ft_rtr_exec(argv_cp, EXIT_SUCCESS));
	}
	else
		return (ft_try_paths(argv_cp));
}

int		ft_exec(t_cmd *cmd)
{
	g_shell.cpid = fork();
	if (!g_shell.cpid)
		exit(ft_exec_paths(cmd));
	waitpid(g_shell.cpid, &g_shell.status, 0);
	if (WEXITSTATUS(g_shell.status) == 127)
		return (ft_error_127(cmd));
	else if (WEXITSTATUS(g_shell.status) == 128)
		return (ft_error_128(cmd));
	else if (WEXITSTATUS(g_shell.status) == 129)
		return (ft_error_129(cmd));
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
