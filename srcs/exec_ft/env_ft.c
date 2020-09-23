/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 18:44:37 by abarot            #+#    #+#             */
/*   Updated: 2020/09/14 15:19:47 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_show_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], 1);
		i++;
	}
}

int		ft_varsize(char *var, char sep)
{
	int i;

	i = 0;
	while (var[i] && var[i] != sep)
		i++;
	if (!var[i])
		return (0);
	return (i);
}

char	*ft_search_var(char **envp, char *str)
{
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], str, ft_varsize(envp[i], '=')))
		i++;
	if (envp[i])
		return (ft_substr(str, 0, ft_varsize(envp[i], '=')));
	return (0);
}

char	*ft_get_value(char **envp, char *var, char sep)
{
	int i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], var, 
						ft_max_value(ft_varsize(envp[i], '='), ft_varsize(var, '='))))
		i++;
	if (ft_strchr(envp[i], sep))
		return (ft_strchr(envp[i], sep) + 1);
	return (0);
}

void	ft_append_env(char *str)
{
	int i;

	i = 0;
	if (!ft_strchr(str, '='))
		return ;
	while (g_shell.envp[i] && ft_strncmp(str, g_shell.envp[i], 
			ft_max_value(ft_varsize(g_shell.envp[i], '='), ft_varsize(str, '='))))
		i++;
	if (!g_shell.envp[i])
	{
		g_shell.envp[i] = ft_strdup(str);
		ft_append_elt(&g_garb_cltor, g_shell.envp[i]);
		g_shell.envp[i + 1] = 0;
	}
	else 
		g_shell.envp[i] = ft_strdup(str);
}

void ft_retreive_env(char *str)
{
	int i;

	i = 0;
	while (g_shell.envp[i] && ft_strncmp(str, g_shell.envp[i], 
			ft_max_value(ft_varsize(g_shell.envp[i], '='), ft_varsize(str, '='))))
		i++;
	if (!ft_strncmp(str, g_shell.envp[i], ft_strlen(str)))
	{
		while (g_shell.envp[i + 1])
		{
			g_shell.envp[i] = g_shell.envp[i + 1];
			i++;
		}
			g_shell.envp[i] = 0;
	}
}
