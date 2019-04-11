/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 03:37:18 by onahiz            #+#    #+#             */
/*   Updated: 2018/11/26 22:06:26 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# define BUFF_SIZE 4096

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isprint(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_isgraph(int c);
int					ft_iscntrl(int c);
int					ft_isblank(int c);
int					ft_isspace(int c);
int					ft_isxdigit(int c);
int					ft_atoi(const char *str);
int					ft_str_is_alpha(const char *str);
int					ft_printf(const char *format, ...);
int					ft_str_is_numeric(const char *str);
int					ft_str_is_printable(const char *str);
int					ft_str_is_lowercase(const char *str);
int					ft_str_is_uppercase(const char *str);
int					get_next_line(const int fd, char **line);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strequ(const char *s1, const char *s2);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strnequ(const char *s1, const char *s2, size_t n);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strnjoin(char const *s1, char const *s2, size_t n);
char				*ft_strnstr(const char *h, const char *n, size_t len);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strncat(char *dst, const char *src, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strcat(char *dst, const char *src);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strndup(const char *src, size_t n);
char				**ft_strsplit(const char *s, char c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strcapitalize(char *str);
char				*ft_strdup(const char *src);
char				*ft_strtrim(char const *s);
char				*ft_strlowcase(char *str);
char				*ft_strupcase(char *str);
char				*ft_strnew(size_t size);
char				*ft_itoa(int n);
void				ft_putnbr(int nb);
void				ft_putchar(char c);
void				ft_strclr(char *s);
void				ft_memdel(void **ap);
void				ft_strdel(char **as);
void				ft_putstr(char const *s);
void				*ft_memalloc(size_t size);
void				ft_putendl(char const *s);
void				ft_putnbr_fd(int nb, int fd);
void				ft_putchar_fd(char c, int fd);
void				*ft_bzero(void *s, size_t len);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_lstadd(t_list **alst, t_list *new);
void				*ft_memset(void *s, int c, size_t len);
void				ft_striter(char *s, void (*f)(char *));
void				*ft_memchr(const void *s, int c, size_t n);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
size_t				ft_strlen(const char *str);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(const void *content, size_t content_size);
unsigned int		ft_basetoi(char *str, char *base_from);

#endif
