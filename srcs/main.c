/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:37:55 by abarot            #+#    #+#             */
/*   Updated: 2020/09/29 20:10:56 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_show_prompt_line()
{
	ft_putstr_fd(ANSI_COLOR_BLUE, 1);
	if (ft_get_value(g_shell.envp, "USER", '='))
	{
		ft_putstr_fd(ft_get_value(g_shell.envp, "USER", '='), 1);
		ft_putstr_fd(":", 1);
	}
	else if (ft_get_value(g_shell.envp, "LOGNAME", '='))
	{
		ft_putstr_fd(ft_get_value(g_shell.envp, "LOGNAME", '='), 1);
		ft_putstr_fd(":", 1);
	}
	else
		ft_putstr_fd("minishell:", 1);
	ft_putstr_fd(ANSI_COLOR_GREEN, 1);
	ft_putstr_fd(g_shell.r_cwd, 1);
	write (1, "$ " , 2);
	ft_putstr_fd(ANSI_COLOR_RESET, 1);
}

int		ft_syntax_ok(char *cmd_line, char c)
{
	int		i;

	i = 0;
	while (*cmd_line)
	{
		while (*(cmd_line + i) && (*(cmd_line + i) != c ||
			(*(cmd_line + i) == c && ((ft_count_elt(cmd_line + i, "\"") % 2) ||
					(ft_count_elt(cmd_line + i, "\'") % 2)))))
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

int		ft_read_input()
{
	char *line;
	char *cmd_line;
	char *cmd_line_r;

	ft_show_prompt_line();
	while (get_next_line(0, &line) == 1)
	{
		// if (line[0] == 27 && line[1] == 91 && line[2] == 68)
            // tputs(tgoto(g_tcap.cm_cap, g_tcap.num_co, g_tcap.num_li - 1), 1, putchar);
		// if (line[0] == 27 && line[1] == 91 && line[2] == 67)
            // tputs(tgoto(g_tcap.cm_cap, g_tcap.num_co, g_tcap.num_li + 1), 1, putchar);
		cmd_line = ft_multiline_mng(line); 
		cmd_line_r = ft_get_cmd_r(cmd_line); 
		if (ft_syntax_ok(cmd_line_r, ';') && ft_syntax_ok(cmd_line_r, '|'))
			ft_parse_cmdline(cmd_line_r);
		ft_show_prompt_line();
	}
	ft_putendl_fd("exit", 1);
	return (EXIT_SUCCESS);
}

// int		ft_init_tcap()
// {
// 	if (tgetent(NULL, ft_get_value(g_shell.envp, "TERM", '=')) == -1)
// 	{
// 		ft_putstr_fd("\nTermcap not defined, exiting\n", STDOUT_FILENO);
// 		return (EXIT_FAILURE);
// 	}
// 	g_tcap.cm_cap = tgetstr("cm", NULL);
// 	g_tcap.cl_cap = tgetstr("cl", NULL);
// 	g_tcap.num_co = tgetnum("co");
// 	g_tcap.num_li = tgetnum("li");
// 	return (EXIT_SUCCESS);
// }

int		ft_init_shell(char **envp)
{
	g_shell.cpid = 0;
	g_shell.envp = envp;
	if (!(g_shell.tilde = ft_get_value(g_shell.envp, "HOME", '=')))
	{
		if (ft_get_value(g_shell.envp, "LOGNAME", '='))
		{
			g_shell.tilde = ft_strjoin("/home/",
					ft_get_value(g_shell.envp, "LOGNAME", '='));
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
	signal(SIGINT, ft_inthandler); 
	signal(SIGQUIT, ft_quithandler);
	if (!ac || !av || !envp)  
		return (EXIT_FAILURE);
	ft_init_shell(envp);
	// if (ft_init_tcap() == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	if (ft_read_input() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_clear_list(&g_garb_cltor);
	return (EXIT_SUCCESS);
}
