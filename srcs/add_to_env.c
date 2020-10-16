/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:20:13 by tbigot            #+#    #+#             */
/*   Updated: 2020/10/15 15:41:29 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		change_env_(t_cmd *cmd)
{
	char	*env_;
	t_rdr	*rdr;
	int		i;

	i = 0;
	rdr = cmd->rdr;
	while (rdr)
	{
		if (rdr->e_rdr == RDR_IN_FEED ||
		rdr->e_rdr == RDR_IN)
		{
			ft_append_env(g_shell.envp, "_=");
			return ;
		}
		rdr = rdr->next;
	}
	while (cmd->argv[i])
		i++;
	env_ = ft_strjoin("_=", cmd->argv[i - 1]);
	ft_append_env(g_shell.envp, env_);
	ft_append_elt(&g_garb_cltor, env_);
}

void		inc_shlvl(char **envp)
{
	int		i;
	char	*shlvl_nb;
	char	*shlvl_txt;

	i = ft_atoi(ft_get_env(envp, "SHLVL", '='));
	i++;
	shlvl_nb = ft_itoa(i);
	shlvl_txt = ft_strjoin("SHLVL=", shlvl_nb);
	if (shlvl_nb)
		free(shlvl_nb);
	ft_append_elt(&g_garb_cltor, shlvl_txt);
	ft_append_env(envp, shlvl_txt);
}
