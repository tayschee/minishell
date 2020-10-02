/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:31:34 by abarot            #+#    #+#             */
/*   Updated: 2020/10/02 16:15:12 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# define BUFFER_SIZE	15

typedef struct s_list	t_list;

struct					s_list
{
	void				*data;
	t_list				*next;
};

enum					e_fdends
{
	RD_END = 0,
	WR_END = 1,
};

int						ft_atoi(const char *s);
void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t num, size_t size);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						ft_isspace(char c);
int						ft_isprint(int c);
void					*ft_memccpy(void *dest, const void *src, int c,
						size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memmove(void *dest, const void *src, size_t n);
void					ft_putnbr_fd(int n, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putchar_fd(char c, int fd);
void					*ft_memset(void *p, int c, size_t n);
void					ft_putstr_fd(char *s, int fd);
char					**ft_split(char const *s, char c);
char					*ft_strchr(const char *s, int c);
char					*ft_strdup(const char *s);
char					*ft_strjoin(char *s1, char *s2);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
size_t					ft_strlcpy(char *dst, const char *src, size_t n);
size_t					ft_strlen(const char *s);
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
						char));
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strrchr(const char *s, int c);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_substr(char const *s, unsigned int start,
						size_t len);
int						ft_tolower(int c);
int						ft_toupper(int c);
char					*ft_strnstr(const char *str, const char *to_find,
						size_t n);
char					*ft_reverse_string(char *s);
char					*ft_addtoa(unsigned long n);
char					*ft_char_to_str(int c);
char					*ft_toupper_string(char *str);
char					*ft_itoa(int n);
char					*ft_utoa(unsigned n);
char					*ft_hextoa(unsigned n);
int						get_next_line(int fd, char **line);
char					*ft_remove_in_str(char *str, char *char_set);
char					*ft_replace_in_str(char *old_str, char *to_replace,
						char *elt);
int						ft_count_line(char **map);
int						ft_max_value(int a, int b);
size_t					ft_count_elt(char *str, char *elt);
void					**ft_list_to_array(t_list *list);
int						ft_list_size(t_list *list);
void					ft_clear_list(t_list **list);
int						ft_append_elt(t_list **list, void *elt);
int						ft_issamestr(char *s1, char *s2);
char					*ft_insert(char *str, char *elt, unsigned int index);
char					*ft_get_word(char *str);
char					*ft_get_string(char *str);
char					*ft_delete(char *str, char *elt, unsigned int index);
int						ft_putchar(int c);
void					ft_clear_tab(char **tab);
char					*ft_replace(char *old_str, char *to_rpl, char *elt,
						int index);
char					*ft_strnchr(const char *s, int c, unsigned int n);
int						ft_varsize(char *var, char sep);
void					ft_show_tab(char **envp);
char					*ft_get_env(char **envp, char *var, char sep);
void					ft_retreive_env(char **envp, char *str);
void					ft_append_env(char **envp, char *str);
char					*ft_search_var(char **envp, char *str);
void					ft_restore_stdfd(int *p_fd, int *saved_fd);
void					ft_init_stdfd(int *n_fd, int *saved_fd);
void					ft_replace_stdfd(int *n_fd);
#endif
