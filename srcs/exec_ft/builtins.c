/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 14:55:25 by abarot            #+#    #+#             */
/*   Updated: 2020/10/07 16:31:13 by abarot           ###   ########.fr       */
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
	free(tmp);
	ft_set_cwd();
	tmp = ft_strjoin("PWD=", g_shell.cwd);
	ft_append_env(g_shell.envp, tmp);
	free(tmp);
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
	int i;

	i = 0;
	if (!cmd->argv[1])
	{
		free(cmd->argv[0]);
		free(cmd->argv);
		if (!(cmd->argv = ft_calloc(2, sizeof(char *))) ||
			!(cmd->next = ft_calloc(1, sizeof(t_cmd))) ||
			!(cmd->next->argv = ft_calloc(2, sizeof(char *))))
			return ;
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
		// free_cmd_list(&cmd);
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

