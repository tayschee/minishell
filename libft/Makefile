# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarot <abarot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 12:18:43 by abarot            #+#    #+#              #
#    Updated: 2020/09/24 17:37:40 by abarot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	./libft.a

SRCS	=	srcs/ft_addtoa.c srcs/ft_atoi.c srcs/ft_bzero.c srcs/ft_calloc.c srcs/ft_char_to_str.c \
			srcs/ft_hextoa.c srcs/ft_isalnum.c srcs/ft_isalpha.c srcs/ft_isascii.c srcs/ft_isdigit.c \
			srcs/ft_isprint.c srcs/ft_itoa.c srcs/ft_memccpy.c srcs/ft_memchr.c srcs/ft_memcmp.c \
			srcs/ft_memcpy.c srcs/ft_memmove.c srcs/ft_memset.c srcs/ft_putchar_fd.c srcs/ft_putendl_fd.c \
			srcs/ft_putnbr_fd.c srcs/ft_putstr_fd.c srcs/ft_remove_in_str.c srcs/ft_reverse_string.c \
			srcs/ft_split.c srcs/ft_strchr.c srcs/ft_strdup.c srcs/ft_strjoin.c srcs/ft_strlcat.c \
			srcs/ft_strlcpy.c srcs/ft_strlen.c srcs/ft_strmapi.c srcs/ft_strncmp.c srcs/ft_strnstr.c \
			srcs/ft_strrchr.c srcs/ft_strtrim.c srcs/ft_substr.c srcs/ft_tolower.c \
			srcs/ft_toupper.c srcs/ft_toupper_string.c srcs/ft_utoa.c srcs/get_next_line.c \
			srcs/ft_count_line.c srcs/ft_max_value.c srcs/ft_count_elt.c srcs/ft_replace_in_str.c \
			srcs/ft_list_size.c srcs/ft_list_to_array.c srcs/ft_clear_list.c srcs/ft_append_elt.c \
			srcs/ft_isspace.c srcs/ft_issamestr.c srcs/ft_insert.c srcs/ft_get_word.c srcs/ft_get_string.c \
			srcs/ft_delete.c srcs/ft_putchar.c

OBJS	=	$(SRCS:.c=.o)

INCLUDE	=	../include

CFLAGS	=	-Werror -Wall -Wextra

RM	=	rm -f

%.o : %.c
	gcc -c $< -o $@ -I$(INCLUDE)

all	:
		make $(NAME)

$(NAME) :	$(OBJS)
			ar -rc $@ $(OBJS)
			ranlib $@

clean	:
		$(RM) $(OBJS) 

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all