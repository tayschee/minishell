/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:37:55 by abarot            #+#    #+#             */
/*   Updated: 2020/10/20 13:07:50 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_show_prompt_line(void)
{
	ft_putstr_fd(ANSI_COLOR_BLUE, 1);
	if (ft_get_env(g_shell.envp, "USER", '='))
	{
		ft_putstr_fd(ft_get_env(g_shell.envp, "USER", '='), 1);
		ft_putstr_fd(":", 1);
	}
	else if (ft_get_env(g_shell.envp, "LOGNAME", '='))
	{
		ft_putstr_fd(ft_get_env(g_shell.envp, "LOGNAME", '='), 1);
		ft_putstr_fd(":", 1);
	}
	else
		ft_putstr_fd("minishell:", 1);
	ft_putstr_fd(ANSI_COLOR_GREEN, 1);
	ft_putstr_fd(g_shell.r_cwd, 1);
	write(1, "$ ", 2);
	ft_putstr_fd(ANSI_COLOR_RESET, 1);
}

int		ft_read_input(void)
{
	char *line;
	char *cmd_l;

	ft_show_prompt_line();
	while (get_next_line(STDIN_FILENO, &line) == 1)
	{
		cmd_l = ft_multiline_mng(line);
		g_shell.in_multil = 0;
		cmd_l = ft_get_cmd_r(cmd_l);
		if (cmd_l)
			(syntax(cmd_l, ';') && syntax(cmd_l, '|') && notempty(cmd_l)) ?
			ft_get_subcmd(cmd_l) : free(cmd_l);
		if (g_shell.exit == 1)
			break ;
		ft_show_prompt_line();
	}
	if (g_shell.exit == 0)
	{
		(line) ? free(line) : 0;
		ft_putendl_fd("exit", 1);
	}
	return (EXIT_SUCCESS);
}

int		ft_init_shell(char **envp)
{
	g_shell.cpid = 0;
	g_shell.in_multil = 0;
	g_shell.exit = 0;
	g_shell.envp = envp;
	if (!(g_shell.tilde = ft_get_env(g_shell.envp, "HOME", '=')))
	{
		if (ft_get_env(g_shell.envp, "LOGNAME", '='))
		{
			g_shell.tilde = ft_strjoin("/home/",
					ft_get_env(g_shell.envp, "LOGNAME", '='));
			ft_append_elt(&g_garb_cltor, g_shell.tilde);
		}
		else
			g_shell.tilde = 0;
	}
	ft_set_cwd();
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av, char **envp)
{
	g_garb_cltor = 0;
	inc_shlvl(envp);
	ft_init_shell(envp);
	ft_append_env(envp, "_=minishell");
	signal(SIGINT, ft_inthandler);
	signal(SIGQUIT, ft_quithandler);
	if (!ac || !av || !envp)
		return (EXIT_FAILURE);
	if (ft_read_input() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_clear_list(&g_garb_cltor);
	return (EXIT_SUCCESS);
}
