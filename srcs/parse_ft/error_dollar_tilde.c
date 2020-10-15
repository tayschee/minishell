/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_dollar_tilde.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbigot <tbigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 15:31:51 by tbigot            #+#    #+#             */
/*   Updated: 2020/10/15 17:09:38 by tbigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		end_of_tilde(char *txt)
{
	int	i;

	i = 0;
	while (txt[i] && txt[i] != ' ')
		i++;
	return(i);
}

int		bad_character_in_tilde(char *bad_c, char *in_tilde, char end)
{
	int 	i;
	int 	j;

	i = 0;
	while (in_tilde[i] && in_tilde[i] != end)
	{
		j = 0;
		while(bad_c[j])
		{
			if (in_tilde[i] == bad_c[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		verif_export_word(char *txt)
{
	int 	ret;

	ret = 1;
	printf("%s\n", txt);
	if (ft_strchr("}~^&()+=[]%%\"'\\|.,><:; ", *txt))
		ret = 0;
	if (!bad_character_in_tilde("${&*()[];' \"\\|<>.", txt, '='))
		ret = 0;
	if (ret == 0)
	{
		write(2, "bash: export: « ", 17);
		write(2, txt, end_of_tilde(txt));
		ft_putendl_fd(" » : identifiant non valable", 2);
	}
	printf("ret : %d\n", ret);
	return (ret);	
}