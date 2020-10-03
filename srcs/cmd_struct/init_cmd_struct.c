/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 14:30:19 by abarot            #+#    #+#             */
/*   Updated: 2020/10/03 14:53:03 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	what_operator(char *operator, char *rdr_list)
{
	int	n;
	int	i;
	int	j;

	i = 0;
	j = -1;
	if (operator)
	{
		while (rdr_list[i])
		{
			n = 0;
			while (rdr_list[i + n] && rdr_list[i + n] != ' ')
				n++;
			j++;
			if (!ft_strncmp(operator, &rdr_list[i], ft_strlen(operator)))
				return (j);
			i += n;
			if (rdr_list[i])
				i++;
		}
	}
	return (-1);
}

static int	cmd_by_cmd(char **cmd, char *operator)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			j = 0;
			while (operator[j])
			{
				n = 0;
				while (operator[j + n] && operator[j + n] != ' ')
					n++;
				if (!ft_strncmp(cmd[i], &operator[j], n))
					return (i);
				j += n;
				if (operator[j])
					j++;
			}
			i++;
		}
	}
	return (-1);
}

void		ft_init_rdr_bis(t_rdr *rdr, char **cmd_char)
{
	rdr->path = NULL;
	rdr->next = NULL;
	rdr->e_rdr = what_operator(cmd_char[0], RDR_LIST);
	free(cmd_char[0]);
	cmd_char[0] = NULL;
}

static char	**ft_init_rdr(t_cmd **cmd, char **cmd_char, t_rdr **next)
{
	int		i;
	int		n;
	t_rdr	*rdr;

	if (!(rdr = malloc(sizeof(t_rdr))))
		exit(EXIT_FAILURE);
	ft_init_rdr_bis(rdr, cmd_char);
	i = 1;
	if (!cmd_char[1])
		return (NULL);
	rdr->path = cmd_char[1];
	n = cmd_by_cmd(&cmd_char[1], OPERATOR_LIST);
	while (++i < n)
	{
		free(cmd_char[i]);
		cmd_char[i] = NULL;
	}
	if (n != -1 && ft_strncmp(cmd_char[n + 1], "|", 2))
	{
		cmd_char = &cmd_char[n + 1];
		cmd_char = ft_init_rdr(cmd, cmd_char, &rdr->next);
	}
	*next = rdr;
	return (cmd_char);
}

t_cmd		*char_to_struct_cmd(char **cmd_char)
{
	int		n;
	t_cmd	*cmd;

	if (!cmd_char)
		return (NULL);
	if (!(cmd = malloc(sizeof(t_cmd))))
		exit(1);
	cmd->argv = cmd_char;
	cmd->rdr = NULL;
	cmd->next = NULL;
	cmd->type = path_or_cmd(*cmd_char);
	n = cmd_by_cmd(cmd_char, OPERATOR_LIST);
	if (n != -1 && ft_strncmp(cmd_char[n], "|", 2))
	{
		cmd_char = ft_init_rdr(&cmd, &cmd_char[n], &cmd->rdr);
		while (cmd_char[n] && ft_strncmp(cmd_char[n], "|", 2))
			n++;
	}
	if (n != -1 && cmd_char[n] && !ft_strncmp(cmd_char[n], "|", 2))
	{
		free(cmd_char[n]);
		cmd_char[n] = NULL;
		cmd->next = char_to_struct_cmd(&cmd_char[n + 1]);
	}
	return (cmd);
}
