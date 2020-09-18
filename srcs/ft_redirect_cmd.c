/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:00:15 by abarot            #+#    #+#             */
/*   Updated: 2020/09/15 16:52:40 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(t_list *cmd, int fd_out)
{
	int		lessn;

	lessn = ft_issamestr(cmd->next->data, "-n");
	if (lessn)
		cmd = cmd->next;
	while (cmd->next)
	{
		cmd = cmd->next;
		if (cmd->data)
		{
			ft_putstr_fd(cmd->data, fd_out);
			if (cmd->next)
				write(fd_out, " ", 1);
		}
	}
	if (!lessn)
		write (fd_out, "\n", 1);
}

void	cd_cmd(t_list *cmd)
{
	char	*tmp;

	if (ft_list_size(cmd) == 1)
	{
		if (chdir(ft_get_value(g_shell.envp, "HOME", '=')) == -1)
			ft_putendl_fd("minishell: cd: HOME not set", 1);
	}
	else if (ft_list_size(cmd) > 2)
		ft_putendl_fd("minishell: cd: too many arguments", 1);
	else if (chdir(cmd->next->data) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(cmd->next->data, 1);
		ft_putendl_fd(": No such file or directory", 1);
	}
	tmp = ft_strjoin("OLDPWD=", g_shell.cwd);
	ft_append_env(tmp);
	ft_append_elt(&g_garb_cltor, tmp);
	ft_set_cwd();
	tmp = ft_strjoin("PWD=", g_shell.cwd);
	ft_append_env(tmp);
	ft_append_elt(&g_garb_cltor, tmp);
}

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

int		ft_exec(t_list *cmd, int fd_in, int fd_out)
{	
	int		instc;
	char	*path_inst;
	char	*path_str;
	char	*first_cmd;
	int		stdin_save;
	int		stdout_save;

	first_cmd = ft_strdup(cmd->data);
	instc = 0;
	if (fd_out != STDOUT_FILENO)
	{
		stdout_save = dup(STDOUT_FILENO);
		dup2(fd_out, STDOUT_FILENO);
	}
	if (fd_in != STDIN_FILENO)
	{
		stdin_save = dup(STDIN_FILENO);
		dup2(fd_in, STDIN_FILENO);
	}
	g_shell.cpid = fork();
	while (1)
	{
		if (g_shell.cpid == -1)
			return (EXIT_FAILURE);
		else if (!g_shell.cpid)
		{
			if (execve(cmd->data, (char **)ft_list_to_array(cmd), g_shell.envp) == -1)
			{
				while ((path_inst = ft_get_path(ft_get_value(g_shell.envp, "PATH", '='), instc)))
				{
					free(cmd->data);
					path_str = ft_strjoin(path_inst, "/");
					ft_append_elt(&g_garb_cltor, path_str);
					path_str = ft_strjoin(path_str, first_cmd);
					cmd->data = path_str;
					if (execve(path_str, (char **)ft_list_to_array(cmd), g_shell.envp) == -1)
						instc++;
					else
						exit(EXIT_SUCCESS);
					free(path_inst);
				}
				ft_putstr_fd(first_cmd, 1);
				ft_putstr_fd(": command not found\n", 1);
				ft_clear_list(&cmd);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&g_shell.cpid);
			if (fd_out != STDOUT_FILENO)
			{
				close(fd_out);
				dup2(stdout_save, STDOUT_FILENO);
				close(stdout_save);
			}
			if (fd_in != STDIN_FILENO)
			{
				close(fd_in);
				dup2(stdin_save, STDIN_FILENO);
				close(stdin_save);
			}
			break;
		}
	}
	return (EXIT_SUCCESS);
}

int		ft_redirect_cmd(t_list *cmd, int fd_in, int fd_out)
{
	if	(ft_issamestr(cmd->data, "exit"))
	{
		ft_clear_list(&cmd);
		ft_append_elt(&g_garb_cltor, g_garb_cltor);
		ft_clear_list(&g_garb_cltor);
		exit(EXIT_SUCCESS);
	}
	else if	(ft_issamestr(cmd->data, "cd"))
		cd_cmd(cmd);
	else if (ft_issamestr(cmd->data, "echo"))
		echo_cmd(cmd, fd_out);
	else if	(ft_issamestr(cmd->data, "pwd"))
		ft_putendl_fd(g_shell.cwd, 1);
	else if	(ft_issamestr(cmd->data, "export"))
		ft_append_env(cmd->next->data);
	else if	(ft_issamestr(cmd->data, "unset"))
		ft_retreive_env(cmd->next->data);
	else if	(ft_issamestr(cmd->data, "env"))
		ft_show_env(g_shell.envp);
	else
		return (ft_exec(cmd, fd_in, fd_out));
	return (EXIT_SUCCESS);
}
