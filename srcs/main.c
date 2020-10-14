/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:37:55 by abarot            #+#    #+#             */
/*   Updated: 2020/10/14 16:23:31 by abarot           ###   ########.fr       */
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

int		syntax(char *cmd_line, char c)
{
	int		i;

	i = 0;
	while (*cmd_line)
	{
		while (*(cmd_line + i) && (*(cmd_line + i) != c || 
			(*(cmd_line + i) == c && ((ft_count_elt(cmd_line + i, "\"") % 2) ||
			(ft_count_elt(cmd_line + i, "\'") % 2) ||
			*(cmd_line + i - 1) == '\\'))))
			i++;
		if (!*(cmd_line + i))
			return (1);
		*(cmd_line + i) = '\0';
		if (ft_count_elt(cmd_line, " ") == ft_strlen(cmd_line))
		{
			*cmd_line = ';';
			ft_putstr_fd("minishell: syntax error near unexpected token '", 1);
			write(1, &c, 1);
			ft_putstr_fd("'\n", 1);
			return (0);
		}
		*(cmd_line + i) = c;
		cmd_line += i + 1;
		i = 0;
	}
	return (1);
}

int		ft_read_input(void)
{
	char *line;
	char *cmd_line;
	char *cmd_line_r;

	ft_show_prompt_line();
	while (get_next_line(STDIN_FILENO, &line) == 1)
	{
		cmd_line = ft_multiline_mng(line);
		g_shell.in_multil = 0;
		cmd_line_r = ft_get_cmd_r(cmd_line);
		if (cmd_line_r && syntax(cmd_line_r, ';') && syntax(cmd_line_r, '|'))
		{
			ft_get_subcmd(cmd_line_r);
			free(cmd_line_r);
		}
		if (g_shell.exit == 1)
			break ;
		ft_show_prompt_line();
	}
	if (g_shell.exit == 0)
	{
		free(line);
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
	signal(SIGINT, ft_inthandler);
	signal(SIGQUIT, ft_quithandler);
	if (!ac || !av || !envp)
		return (EXIT_FAILURE);
	if (ft_read_input() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_clear_list(&g_garb_cltor);
	return (EXIT_SUCCESS);
}
