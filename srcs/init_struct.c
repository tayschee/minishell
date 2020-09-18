#include "minishell.h"

void	ft_init_shell(char **envp)
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
}

static int     path_or_cmd(const char *txt, const char *cmd_list)
{
    int n;
    int i;

    i = 0;
    while (cmd_list[i])
    {
        n = 0;
        while(cmd_list[i + n] && cmd_list[i + n] != ' ')
            n++;
		printf("n : %d\n", n);
        if (!ft_strncmp(txt, &cmd_list[i], n))
			return (CMD);
        i += n;
        if (cmd_list[i])
            i++;
    }
	return (PATH);

}

void ft_init_cmd(char **cmd_char)
{
	int i;

	(void)cmd_char;

	i = path_or_cmd(*cmd_char, CMD_LIST);
	printf("i : %d\n", i);
	/*t_cmd	*cmd;

	if (!(malloc(sizeof(t_cmd))))
		exit(1);// fonction pour quitte
	cmd->e_type*/
}