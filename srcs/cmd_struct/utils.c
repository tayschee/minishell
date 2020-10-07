/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 14:46:13 by abarot            #+#    #+#             */
/*   Updated: 2020/10/07 10:48:43 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			this_is_operator(char *cmd, char *operator)
{
	int	i;
	int	n;
	int	j;

	i = 0;
	j = -1;
	while (operator[i])
	{
		n = 0;
		while (operator[i + n] && operator[i + n] != ' ')
			n++;
		j++;
		if (!ft_strncmp(cmd, &operator[i], n))
			return (i);
		i += n;
		if (operator[i])
			i++;
	}
	return (-1);
}

int			count_struct(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int			path_or_cmd(char *argv)
{
	if (ft_issamestr(argv, "exit") || ft_issamestr(argv, "cd") ||
		ft_issamestr(argv, "echo") || ft_issamestr(argv, "pwd") ||
		ft_issamestr(argv, "export") || ft_issamestr(argv, "unset") ||
		ft_issamestr(argv, "env"))
		return (CMD);
	return (PATH);
}

char    quote_management(char *txt)
{
    char    c;
    int     i;

    i = 0;
    c = 0;
    while (txt[i])
    {
        if (txt[i] == '\\')
            c = txt[i++];
        else if (txt[i] == '"' || txt[i] == '\'')
            c = txt[i];
        while ((c == '"' || c == '\'') && txt[++i])
        {
            if (txt[i] == c)
            {
                c = 0;
                break;
            }
        }
        if (txt[i])
        {
            c = 0;
            i++;
        }
    }
    return (c);
}

void	inc_shlvl(char **envp)
{
	int i;
	char *shlvl_nb;
	char *shlvl_txt;

	i = ft_atoi(ft_get_env(envp, "SHLVL", '='));
	i++;
	shlvl_nb = ft_itoa(i);
	shlvl_txt = ft_strjoin("SHLVL=", shlvl_nb);
	if (shlvl_nb)
		free(shlvl_nb);
	ft_append_elt(&g_garb_cltor, shlvl_txt);
	ft_append_env(envp, shlvl_txt);
}