# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarot <abarot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/02 20:31:48 by abarot            #+#    #+#              #
#    Updated: 2020/10/20 11:30:04 by abarot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	=	srcs/main.c \
			srcs/signal_handling.c \
			srcs/parse_ft/multiline_mng.c \
			srcs/parse_ft/get_cmd_r.c \
			srcs/parse_ft/brackets.c \
			srcs/parse_ft/syntax_ft.c \
			srcs/parse_ft/get_subcmd.c \
			srcs/cmd_struct/cmd_parsing.c \
			srcs/cmd_struct/ft_get_argv.c \
			srcs/cmd_struct/backslash.c \
			srcs/cmd_struct/free_cmd.c \
			srcs/cmd_struct/init_cmd_struct.c \
			srcs/cmd_struct/utils.c \
			srcs/exec_ft/cmd_treatment.c \
			srcs/exec_ft/ft_redirect_cmd.c \
			srcs/exec_ft/paths_ft.c \
			srcs/exec_ft/builtins.c \
			srcs/exec_ft/ft_exec_pipe.c \
			srcs/exec_ft/ft_exec_pipe_2.c \
			srcs/exec_ft/redirect_ft.c \
			srcs/add_to_env.c \
			srcs/parse_ft/error_dollar_tilde.c
			
OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror

INCL	=	include

LIB 	=  libft.a

LIB_PATH	=	libft

RM	=	rm -f
			
%.o : %.c
		gcc $(CFLAGS) -c $< -o $@ -I$(INCL)

all	:	
		make -C libft
		make $(NAME)

$(NAME)	: $(OBJS) 
			gcc -g $(CFLAGS) $(OBJS) -lcurses -L./libft/. -lft -o $(NAME) -I$(INCL)
			
clean	:
		$(RM) $(OBJS) && make -C libft fclean

fclean	:	clean
		$(RM) $(NAME) 

re	:	fclean all