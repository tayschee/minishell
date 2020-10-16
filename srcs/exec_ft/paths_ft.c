/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:12:53 by abarot            #+#    #+#             */
/*   Updated: 2020/10/16 19:09:16 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(char *paths, int instc)
{
	int		path_s;
	int		path_end;
	char	*path;
	char	*tmp;

	path_s = 0;
	while (paths[path_s] && instc)
	{
		if (paths[path_s] == ':')
			instc--;
		path_s++;
	}
	if (!paths[path_s])
		return (0);
	if (paths[path_s] == ':')
		path_s++;
	path_end = path_s + 1;
	while (paths[path_end] && paths[path_end] != ':')
		path_end++;
	tmp = ft_substr(paths, path_s, path_end - path_s);
	path = ft_strjoin(tmp, "/");
	free(tmp);
	return (path);
}

int		ft_is_a_path(char *path)
{
	if (path[0] == '/')
		return (1);
	if (path[0] == '.' && path[1] == '/')
		return (1);
	if (path[0] == '.' && path[1] == '.' && path[2] == '/')
		return (1);
	return (0);
}
