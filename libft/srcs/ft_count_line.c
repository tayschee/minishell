/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 17:01:33 by abarot            #+#    #+#             */
/*   Updated: 2020/09/03 13:56:48 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_count_line(char **lines)
{
	int	line_nb;

	if (!lines)
		return (0);
	line_nb = 0;
	while (lines[line_nb])
		line_nb++;
	return (line_nb);
}
