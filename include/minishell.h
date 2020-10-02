/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:40:09 by abarot            #+#    #+#             */
/*   Updated: 2020/10/02 16:48:09 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"
# define PATH_MAX        	4096

# define CMD_LIST "exit cd export unset env echo"
# define OPERATOR_LIST "> >> < | <<"
# define RDR_LIST "> >> <"

# define UNEXP_NL "minishell: syntax error near unexpected token `newline'\n"

typedef struct s_cmd	t_cmd;
typedef struct s_rdr	t_rdr;

enum					e_type
{
	CMD,
	PATH,
};

enum					e_rdr
{
	RDR_OUT,
	RDR_OUT_APPEND,
	RDR_IN,
};

struct					s_rdr
{
	int					e_rdr;
	char				*path;
	t_rdr				*next;
};

struct					s_cmd
{
	int					type;
	char				**argv;
	t_rdr				*rdr;
	t_cmd				*next;
};

typedef struct			s_tcap
{
	char				*cl_cap;
	char				*cm_cap;
	int					num_co;
	int					num_li;
}						t_tcap;

typedef struct			s_shell
{
	char				*cwd;
	char				*r_cwd;
	char				**envp;
	char				*tilde;
	int					status;
	pid_t				cpid;
	struct stat			stat;
}						t_shell;

t_shell g_shell;
t_tcap g_tcap;
t_list *g_garb_cltor;

void					ft_set_cwd();
void					ft_show_prompt_line();
char					*ft_multiline_mng(char *line);
char					*ft_get_cmd_r(char *cmd_line);
int						ft_parse_cmdline(char *cmd_line);
int						ft_manage_rdr(t_cmd *cmd);
int						ft_redirect_cmd(t_cmd *cmd);
int						ft_exec(t_cmd *cmd);
int						ft_redirection(t_rdr *rdr, int *p_fd);
void					ft_inthandler();
void					ft_quithandler();
t_cmd					*ft_init_cmd(char *unique_cmd);
t_cmd					*char_to_struct_cmd(char **cmd_char);
void					free_cmd_list(t_cmd **cmd);
int						this_is_operator(char *txt, char *operator);
int						ft_cmd_treatment(t_cmd *cmd);
void					ft_exec_paths(t_cmd *cmd);
int						count_struct(t_cmd	*cmd);
t_cmd					*fork_all(t_cmd *cmd);
char					*cmd_without_bs(char *cmd);
#endif
