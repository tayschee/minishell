/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:00:15 by abarot            #+#    #+#             */
/*   Updated: 2020/10/02 11:46:40 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_cwd()
{
	g_shell.cwd = getcwd(g_shell.cwd, PATH_MAX);
	if (!(g_shell.r_cwd = ft_replace_in_str(g_shell.cwd, g_shell.tilde, "~")))
	{	
		free(g_shell.r_cwd);
		g_shell.r_cwd = ft_strdup(getcwd(g_shell.cwd, PATH_MAX));
	}
	ft_append_elt(&g_garb_cltor, g_shell.r_cwd);
}

void	echo_cmd(char **argv)
{
	int		lessn;
	int		i;

	i = 1;
	lessn = ft_issamestr(argv[1], "-n");
	if (lessn)
		i = 2;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!lessn)
		write (STDOUT_FILENO, "\n", 1);
}

void	cd_cmd(t_cmd *cmd)
{
	char	*tmp;

	if (!cmd->argv[1])
	{
		if (chdir(ft_get_env(g_shell.envp, "HOME", '=')) == -1)
			ft_putendl_fd("minishell: cd: HOME not set", 1);
	}
	else if (cmd->argv[2])
		ft_putendl_fd("minishell: cd: too many arguments", 1);
	else if (chdir(cmd->argv[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(cmd->argv[1], 1);
		ft_putendl_fd(": No such file or directory", 1);
	}
	tmp = ft_strjoin("OLDPWD=", g_shell.cwd);
	ft_append_env(g_shell.envp, tmp);
	free(tmp);
	ft_set_cwd();
	tmp = ft_strjoin("PWD=", g_shell.cwd);
	ft_append_env(g_shell.envp, tmp);
	free(tmp);
}

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

void	ft_export_cmd(t_cmd *cmd)
{
	int i;

	i = 0;
	if (!cmd->argv[1])
	{
		free(cmd->argv[0]);
		free(cmd->argv);
		if (!(cmd->argv = ft_calloc(3, sizeof(char *))))
			return ;
		cmd->argv[0] = ft_strdup("declare");
		cmd->argv[1] = ft_strdup("-x");
		ft_exec(cmd);
	}
	else
	{
		while (cmd->argv[i + 1])
		{
			ft_append_env(g_shell.envp, cmd->argv[i + 1]);
			i++;
		}
	}
}

int		ft_redirect_cmd(t_cmd *cmd)
{
	if	(ft_issamestr(cmd->argv[0], "exit"))
		exit(EXIT_SUCCESS);
	else if	(ft_issamestr(cmd->argv[0], "cd"))
		cd_cmd(cmd);
	else if (ft_issamestr(cmd->argv[0], "echo"))
		echo_cmd(cmd->argv);
	else if	(ft_issamestr(cmd->argv[0], "pwd"))
		ft_putendl_fd(g_shell.cwd, 1);
	else if	(ft_issamestr(cmd->argv[0], "export"))
		ft_export_cmd(cmd);
	else if	(ft_issamestr(cmd->argv[0], "unset"))
		ft_unset_cmd(cmd->argv);
	else if	(ft_issamestr(cmd->argv[0], "env"))
		ft_show_tab(g_shell.envp);
	return (EXIT_SUCCESS);
}
