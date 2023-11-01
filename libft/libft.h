/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:11:14 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/01 22:09:16 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef GNL_BUFFER
#  define GNL_BUFFER 10
# endif

// for gnl

# define CLEAN 1
# define READ 2

// Optimisation? What do you mean?

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}					t_list;

// Part 1

size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
int					ft_strlen(const char *str);
char				*ft_strnstr(char *str, char *to_find, size_t len);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memset(void *s, int c, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strchr(const char *s, int c);
void				ft_bzero(void *s, size_t n);
int					ft_strncmp(char *s1, char *s2, unsigned int n);
int					ft_atoi(const char *str);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_isalpha(int c);
int					ft_isprint(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(char *src);

// Part 2

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strjoin(char *s1, char *s2);
char				**ft_split(char const *s, char c);
int					ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
int					ft_putnbr_fd(int n, int fd);
char				*ft_itoa(int n);

// Part 3

t_list				*ft_lstnew(char *key, char *value);
t_list				*ft_lstnew(char *key, char *value);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(char *, char *));
void				ft_lstclear(t_list **lst, void (*del)(char *, char *));
void				ft_lstiter(t_list *lst, void (*f)(char *, char *));
void				ft_lstdelone(t_list *lst, void (*del)(char *, char *));
void				ft_lstclear(t_list **lst, void (*del)(char *, char *));
void				ft_lstiter(t_list *lst, void (*f)(char *, char *));
int					ft_lstsize(t_list *lst);

// printf part

int					ft_printf_fd(int fd, const char *format, ...);
int					ft_putnbru_fd(unsigned int n, int fd);
int					ft_printhex_fd(unsigned long n, char format, int fd);
char				*ft_strstr(char *str, char *to_find);
int					ft_strcmp(char *s1, char *s2);

// Vitalik starter pack

int					ft_tr(int condition, int t, int f);
int					ft_max(int a, int b);
int					ft_min(int a, int b);

size_t				ft_min_s(size_t a, size_t b);
size_t				ft_max_s(size_t a, size_t b);
size_t				ft_abs(int a);

// String utils

char				*ft_strcat(const char *s1, const char *s2);
int					ft_contains(const char *set, char c);
int					ft_is_blank(const char *str);

// Should be helpful

char				*get_next_line(int fd, int mode);
void				ft_free_split(char **strs);
int					ft_len_split(char **split);
void				ft_free(void *data);

#endif
