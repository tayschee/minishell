#include "minishell.h"

static int		what_operator(char *operator, char *rdr_list)
{
	int n;
    int i;
	int	j;

    i = 0;
	j = -1;
	if (operator)
	{
    	while (rdr_list[i])
    	{
        	n = 0;
        	while(rdr_list[i + n] && rdr_list[i + n] != ' ')
            	n++;
			j++;
			printf("rdr_list[i] : %s\n", &rdr_list[i]);
        	if (!ft_strncmp(operator, &rdr_list[i], ft_strlen(operator)))
				return (j);
			printf("n : %d\n", n);
        	i += n;
        	if (rdr_list[i])
            	i++;
    	}
	}
	return (-1);


}


static int     path_or_cmd(const char *txt, const char *cmd_list)
{
    int n;
    int i;

    i = 0;
	if (txt)
	{
    	while (cmd_list[i])
    	{
        	n = 0;
        	while(cmd_list[i + n] && cmd_list[i + n] != ' ')
            	n++;
        	if (!ft_strncmp(txt, &cmd_list[i], n))
				return (CMD);
        	i += n;
        	if (cmd_list[i])
            	i++;
    	}
	}
	return (PATH);
}

static int	cmd_by_cmd(char **cmd, char *operator)
{
	int i;
	int j;
	int n;

	i = 0;
	if (cmd)
	{
		while(cmd[i])
		{
			j = 0;
			while(operator[j])
			{
				n = 0;
				while(operator[j + n] && operator[j + n] != ' ')
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
	return -1;
}

static char  **ft_init_rdr(t_cmd **cmd, char **cmd_char, t_rdr **next)
{
	int		i;
	int		n;
	t_rdr	*rdr;

	i = 1;
	if (!(rdr = malloc(sizeof(t_rdr))))
		exit(1);// fonction pour quitte
	rdr->path = NULL;
	rdr->next = NULL;
	printf("cmd_char[0] : %s\n", cmd_char[0]);
	rdr->e_rdr = what_operator(cmd_char[0], RDR_LIST);
	free(cmd_char[0]);
	cmd_char[0] = NULL;
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

t_cmd *char_to_struct_cmd(char **cmd_char)
{
	int n;
	t_cmd	*cmd;

	if (!cmd_char)
		return (NULL);
	if (!(cmd = malloc(sizeof(t_cmd))))
		exit(1);// fonction pour quitte
	cmd->argv = cmd_char;
	cmd->rdr = NULL;
	cmd->next = NULL;
	cmd->e_type = path_or_cmd(*cmd_char, CMD_LIST);
	n = cmd_by_cmd(cmd_char, OPERATOR_LIST);
	/*if (n != -1 && !ft_strncmp(cmd_char[n], "|", 2))
	{
		free(cmd_char[n]);
		cmd_char[n] = NULL;
		cmd->next = char_to_struct_cmd(&cmd_char[n + 1]);
	}*/
	if (n != -1 && ft_strncmp(cmd_char[n], "|", 2))
	{
		cmd_char = ft_init_rdr(&cmd, &cmd_char[n], &cmd->rdr);
		while (cmd_char[n] && ft_strncmp(cmd_char[n], "|", 2))
			n++;
	}
	if (n != -1 && cmd_char[n] && !ft_strncmp(cmd_char[n], "|", 2))
	{
		printf("pass here\n");
		free(cmd_char[n]);
		cmd_char[n] = NULL;
		cmd->next = char_to_struct_cmd(&cmd_char[n + 1]);
	}
	return (cmd);
}