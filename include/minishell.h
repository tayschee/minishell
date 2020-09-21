/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:40:09 by abarot            #+#    #+#             */
/*   Updated: 2020/09/21 16:08:25 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// todo list :
// 		- gestion pipeline
//			- gestion pipe dans redirection cmd : == thing1 > temp_file && thing2 < temp_file
// 		-  $azezaea ==> chaine nulle
// 		- 'echo azezaeza', echo $? '$?'
// 		- pb gestion des elt dans "" et '' -> si "string test "'"" ex : cd ""'"$HOME"'""
// 		- check memory leeks
// 		- gestion "  ; "
// 		- gestion des droits avec lstat et fstat

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
#include <errno.h>
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"
# define PATH_MAX        	4096

typedef struct s_cmd t_cmd;
typedef struct s_rdr t_rdr;

enum			e_fdends
{
	RD_END = 0,
	WR_END = 1,
};

enum 			e_type
{
	CMD,
	PATH,
};

enum 			e_rdr
{
	RDR_OUT,
	RDR_OUT_APPEND,
	RDR_IN,
};

struct 				s_rdr
{
	int				e_rdr;
	char			*path;
	t_rdr			*next;
};

struct 				s_cmd
{
	int 			type;
	char			**argv;
	t_rdr			*rdr;
	t_cmd			*next_cmd;
};

typedef struct s_shell
{
	char			*cwd;
	char			*r_cwd;
	char			**envp;
	char			*tilde;
	int				l_rtrval;
	pid_t			cpid;
	struct stat		stat;
}				t_shell;

t_shell g_shell;
t_list	*g_garb_cltor;

void	ft_init_shell(char **envp);
void	ft_set_cwd();
void	ft_show_prompt_line();
char	*ft_multiline_mng(char *line);
char	*ft_get_cmd_r(char *cmd_line);
int 	ft_parse_cmdline(char *cmd_line);
int		ft_manage_rdr(t_cmd *cmd);
int		ft_redirect_cmd(t_cmd *cmd);
int		ft_exec(t_cmd *cmd);
void	ft_show_env(char **envp);
void	ft_append_env(char *str);
char	*ft_get_value(char **envp, char *var, char sep);
char	*ft_search_var(char **envp, char *str);
void	ft_retreive_env(char *str);
void	ft_inthandler();
void 	ft_quithandler(); 
#endif