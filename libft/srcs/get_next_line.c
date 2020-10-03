/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:57:29 by abarot            #+#    #+#             */
/*   Updated: 2020/10/02 17:09:47 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_createkeep(char *keep, char *line)
{
	int		i;

	i = 0;
	line = ft_strchr(line, '\n');
	*(line) = '\0';
	line++;
	while (*line)
	{
		keep[i] = *line;
		line++;
		i++;
	}
	keep[i] = '\0';
}

int		ft_read_value(char **line, int fd)
{
	int		rd_val;
	char	*buf;
	char	*tmp;

	if (!(buf = ft_calloc(BUFFER_SIZE + 1, 1)))
		return (-1);
	tmp = *line;
	rd_val = read(fd, buf, BUFFER_SIZE);
	if (rd_val < 0)
		return (-1);
	*line = ft_strjoin(tmp, buf);
	free(buf);
	free(tmp);
	if (rd_val < BUFFER_SIZE && !(ft_strchr(*line, '\n')))
		return (0);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char to_keep[BUFFER_SIZE];
	int			read_value;

	read_value = BUFFER_SIZE;
	if (!line || fd < 0 || !BUFFER_SIZE)
		return (-1);
	*line = ft_strjoin(to_keep, "");
	while (!ft_strchr(*line, '\n'))
	{
		if ((read_value = ft_read_value(line, fd)) == -1)
			return (-1);
		if (!read_value)
			return (0);
	}
	ft_createkeep(to_keep, *line);
	return (1);
}
