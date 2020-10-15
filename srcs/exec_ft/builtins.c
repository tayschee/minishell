/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 14:55:25 by abarot            #+#    #+#             */
/*   Updated: 2020/10/16 13:56:20 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		write(STDOUT_FILENO, "\n", 1);
}

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
	else if (cmd->argv[2] || (val = chdir(cmd->argv[1])) == -1)
	{
		if (cmd->argv[2])
			ft_putendl_fd("minishell: cd: too many arguments", 1);
		else if (val == -1)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(cmd->argv[1], 1);
			ft_putendl_fd(": No such file or directory", 1);
		}
		g_shell.status = EXIT_FAILURE;
		return ;
	}
	ft_create_oldpwd();
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
	int		i;
	int		j;
	char	*cmd_clone;
	char	*tmp;

	i = 0;
	j = 0;
	if (!cmd->argv[1])
		ft_create_env_declare(cmd);
	else
	{
		i = 1;
		while (cmd->argv[i])
		{
			tmp = ft_strdup(cmd->argv[i]);
			ft_append_env(g_shell.envp, tmp);
			ft_append_elt(&g_garb_cltor, tmp);
			while (cmd->argv[i][j] && cmd->argv[i][j] != '=')
				j++;
			tmp = ft_substr(cmd->argv[i], 0, j);
			cmd_clone = ft_strjoin("_=", tmp);
			if (tmp)
				free(tmp);
			ft_append_env(g_shell.envp, cmd_clone);
			ft_append_elt(&g_garb_cltor, cmd_clone);
			i++;
		}
	}
}
