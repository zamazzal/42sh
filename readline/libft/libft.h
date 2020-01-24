/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 11:23:16 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/13 15:45:20 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct	s_splitbs
{
	int			i;
	int			j;
}				t_splitbs;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_need
{
	int				*flag;
	int				width;
	int				precision;
	int				lenth;
	char			conv;
	int				result;
}				t_need;

void			dfree_int(int **nbr);
void			dfre(char **tabe);
void			ft_nbrdel(int **nbr);
void			tfree(char ***array);
int				ft_entier(int x);
int				ft_parite(int x);
int				ft_max(int i, int j);
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystackx, const char *needle);
char			*ft_strnstr(const char *haystack,
const char		*needle, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *nptr);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_memalloc(size_t size);
void			*ft_mema(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar(char c);
void			ft_putstr(char *s);
void			ft_putendl(char *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
char			*ft_searchnreplace(char *str, int s, int r);
char			**ft_split(char *str, char *s);
char			**ft_split_whitespaces(char *str);
char			**ft_splitbs(char *str, int *bs);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int				ft_isspace(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
size_t			ft_lstlen(t_list *lst);
int				ft_printf(const char *format, ...);
char			*ft_jandf(char *a, char *b, int fa, int fb);
int				ft_lenth(const char *format, int *i);
int				*ft_flags(const char *format, int *i, int c, int *s);
char			ft_conversion(const char *format, int *i);
int				ft_width(const char *format, int *i, int r);
char			*ft_cased(t_need a, va_list ap);
char			*ft_cases(t_need a, va_list ap);
int				ft_precision(const char *format, int *i, int r);
t_need			ft_pourcent(const char *format, int *i);
int				get_next_line(const int fd, char **line);
char			*ft_sub2char(char *str, int c);
char			*ft_freesub(char *str, unsigned int start, size_t lenth);
char			**ft_addtotab(char **table, char *line);
int				ft_tablen(char **table);
char			**ft_split_1(char *str, char *charset);

#endif
