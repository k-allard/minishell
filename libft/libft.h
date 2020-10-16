/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 21:17:00 by kallard           #+#    #+#             */
/*   Updated: 2020/10/15 14:58:29 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define LLMAX 		9223372036854775807ull
# define BUF_SIZE	40

typedef	struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_gnl
{
	int				fd;
	char			*remainder;
	struct s_gnl	*next;
}					t_gnl;

void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putstr_fd(char *s, int fd);

int					ft_toupper(int ch);
int					ft_tolower(int ch);
int					ft_isalnum(int ch);
int					ft_isalpha(int ch);
int					ft_isascii(int ch);
int					ft_isspace(int ch);
int					ft_isdigit(int ch);
int					ft_isprint(int ch);
int					ft_atoi(char *str);
char				*ft_itoa(int n);
char				*ft_itoa_convert(unsigned long value, unsigned long base);

char				*ft_strnew(size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strdup(const char *src);
char				*ft_strndup(const char *src, size_t len);
size_t				ft_strlcpy(char *dest, const char *src, size_t destsize);
char				*ft_strcpy(char *dest, const char *src);
size_t				ft_strlcat(char *dest, const char *src, size_t destsize);
char				*ft_strnstr(const char *str, const char *to_find, \
					size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strchr(const char *str, int c);
char				*locate_n(const char *str);
char				*ft_strrchr(const char *str, int c);
void				ft_strfree(char **str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);

int					ft_memcmp(const char *str1, const char *str2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memalloc(size_t size);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),\
					void (*del)(void *));

int					get_next_line(int fd, char **line);

#endif
