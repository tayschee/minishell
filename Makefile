# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarot <abarot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/02 20:31:48 by abarot            #+#    #+#              #
#    Updated: 2020/09/16 14:42:30 by tbigot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	=	srcs/main.c srcs/parse_ft.c srcs/ft_redirect_cmd.c srcs/env_ft.c \
			srcs/pipe_ft.c srcs/signal_handling.c srcs/redirection_ft.c srcs/init_struct.c \
			srcs/cmd_parsing.c
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
			gcc $(CFLAGS) $(OBJS) -L./libft/. -lft -o $(NAME) -I$(INCL)
			
clean	:
		$(RM) $(OBJS) && make -C libft fclean

fclean	:	clean
		$(RM) $(NAME) 

re	:	fclean all
