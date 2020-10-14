/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:28:30 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/03 15:54:21 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <termios.h>

# define C 4
# define D 8
# define S 262144
# define P 32768
# define I 256
# define O 16384
# define X 8388608
# define H 128
# define L 2048
# define F 32
# define XX 8388608
# define LL 2048
# define U 1048576
# define SINT 1
# define SCHR 2
# define LINT 4
# define LLINT 8

typedef signed char				t_schar;
typedef unsigned char			t_uchar;
typedef short int				t_sint;
typedef long int				t_lint;
typedef long long int			t_llint;
typedef unsigned short int		t_usint;
typedef unsigned long int		t_ulint;
typedef unsigned long long int	t_ullint;

typedef struct					s_need5
{
	int i;
	int c;
	int	mc;
}								t_need5;

typedef struct					s_splitbs
{
	int			i;
	int			j;
}								t_splitbs;

typedef struct					s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}								t_list;

typedef struct					s_need
{
	int				*flag;
	int				width;
	int				precision;
	int				lenth;
	char			conv;
	int				result;
}								t_need;

union							u_vars
{
	char			c;
	t_ullint		ui;
	t_llint			ll;
};
typedef union u_vars			t_vars;

char							*ft_strrv(char *dest, const char *src);
char							*ft_strcp(char *dest, const char *src, int a);
char							sign(int x);
void							ft_putendl(char const *s);
void							ft_putchar(char c);
void							ft_putnbr(t_llint nbr);
void							ft_putstr(char const *str);
void							ft_putstr_to(char *str, char c);
void							ft_putuint(t_ullint n);
void							ft_putoctal(t_ullint nbr);
void							ft_puthexa(t_ullint nbr, ushort plus);
void							ft_putendl_fd(char const *s, int fd);
void							ft_putchar_fd(char c, int fd);
void							ft_putnbr_fd(t_llint nbr, int fd);
void							ft_putstr_fd(char const *str, int fd);
void							ft_putstr_to_fd(char *str, char c, int fd);

void							dfree_int(int **nbr);
void							dfre(char **tabe);
void							ft_nbrdel(int **nbr);
void							tfree(char ***array);
int								ft_entier(int x);
int								ft_parite(int x);
int								ft_max(int i, int j);
void							*ft_memset(void *s, int c, size_t n);
void							ft_bzero(void *s, size_t n);
void							*ft_memcpy
(void *dest, const void *src, size_t n);
void							*ft_memccpy
(void *dest, const void *src, int c, size_t n);
void							*ft_memmove
(void *dest, const void *src, size_t n);
void							*ft_memchr
(const void *s, int c, size_t n);
int								ft_memcmp
(const void *s1, const void *s2, size_t n);
char							*ft_strchr
(const char *s, int c);
char							*ft_strrchr(const char *s, int c);
char							*ft_strstr
(const char *haystackx, const char *needle);
char							*ft_strnstr(const char *haystack,
		const char		*needle, size_t len);
int								ft_strcmp(const char *s1, const char *s2);
int								ft_strncmp
(const char *s1, const char *s2, size_t n);
int								ft_atoi(const char *nptr);
int								ft_isalpha(int c);
int								ft_isdigit(int c);
int								ft_isalnum(int c);
int								ft_isascii(int c);
int								ft_isprint(int c);
int								ft_toupper(int c);
int								ft_tolower(int c);
void							*ft_memalloc(size_t size);
void							*ft_mema(size_t size);
void							ft_memdel(void **ap);
char							*ft_strnew(size_t size);
void							ft_strdel(char **as);
void							ft_strclr(char *s);
void							ft_striter(char *s, void (*f)(char *));
void							ft_striteri
(char *s, void (*f)(unsigned int, char *));
char							*ft_strmap(char const *s, char (*f)(char));
char							*ft_strmapi
(char const *s, char (*f)(unsigned int, char));
void							ft_saveinhistory(char *cmd);
void							ret_tab_toline(char *line);
int								ft_clearhash(void);
void							sigs(void);
int								ft_strequ(char const *s1, char const *s2);
char							*ft_strsub
(char const *s, unsigned int start, size_t len);
char							*ft_strjoin(char const *s1, char *s2);
char							*ft_strtrim(char const *s);
char							**ft_strsplit(char const *s, char c);
char							*ft_itoa(int n);
void							ft_putchar(char c);
void							ft_putchar_fd(char c, int fd);
void							ft_putstr_fd(char const *s, int fd);
void							ft_putendl_fd(char const *s, int fd);
char							*ft_searchnreplace(char *str, int s, int r);
char							**ft_split(char *str, char *s);
char							**ft_split_whitespaces(char *str);
char							**ft_splitbs(char *str, int *bs);
t_list							*ft_lstnew
(void const *content, size_t content_size);
void							ft_lstdelone
(t_list **alst, void (*del)(void*, size_t));
void							ft_lstdel
(t_list **alst, void (*del)(void *, size_t));
void							ft_lstadd(t_list **alst, t_list *new);
void							ft_lstiter
(t_list *lst, void (*f)(t_list *elem));
t_list							*ft_lstmap
(t_list *lst, t_list *(*f)(t_list *elem));
int								ft_isspace(int c);
int								ft_islower(int c);
int								ft_isupper(int c);
size_t							ft_lstlen(t_list *lst);
char							*ft_jandf(char *a, char *b, int fa, int fb);
int								ft_lenth(const char *format, int *i);
int								*ft_flags
(const char *format, int *i, int c, int *s);
char							ft_conversion(const char *format, int *i);
int								ft_width(const char *format, int *i, int r);
char							*ft_cased(t_need a, va_list ap);
char							*ft_cases(t_need a, va_list ap);
int								ft_precision(const char *format, int *i, int r);
t_need							ft_pourcent(const char *format, int *i);
int								get_next_line(const int fd, char **line);
char							*ft_sub2char(char *str, int c);
char							*ft_freesub
(char *str, unsigned int start, size_t lenth);
char							**ft_addtotab(char **table, char *line);
int								ft_tablen(char **table);
char							**ft_split_1(char *str, char *charset);

size_t							ft_strclen(const char *str, char c);
void							free_double(char **table);
int								ft_islower(int c);
int								ft_isupper(int c);
char							ft_getchr(void);
int								ft_strccmp
(const char *str, const char *s2, char c);
char							*ft_strndup(const char *str, int size);
char							*ft_strcdup(const char *str, char c);
char							*ft_remplacer_str
(char *chn, char *change, char *nchn);
int								ft_skip_lensep(char const *str, char *sp);
int								ft_skip_sep(const char *str, char *sep);
int								ft_is_separ(char const *str, char c);
char							*ft_reverse(char const *chaine);
int								ft_change_chr_to_nwchr(char *chaine,
		char chr, char nwchr);
int								ft_sqrt(int nb);
t_list							*ft_new_lst(t_list *lst, char *str);
void							ft_print_list(t_list *list);
int								ft_count_char(char const *str);
int								ft_ret_start(char const *str);
int								ft_count_to_find(char *str, char *to_find);
void							ft_rev(char *str);
char							*ft_strccpy
(char *dest, char const *src, char c);
int								ft_wordlen(char const *s, char c);
int								ft_count_word(char *s, char c);
void							ft_lstiter
(t_list *lst, void (*f)(t_list *elem));
void							ft_lstadd(t_list **alst, t_list *new);
void							ft_lstdel
(t_list **alst, void (*del)(void *, size_t));
t_list							*ft_lstmap
(t_list *lst, t_list *(*f)(t_list *elem));
void							ft_lstdelone
(t_list **alst, void (*del)(void *,
			size_t));
t_list							*ft_lstnew
(void const *content, size_t content_size);
void							ft_memdel(void **ap);
void							*ft_memalloc(size_t size);
int								ft_atoi(const char *str);
int								ft_isalnum(int argument);
int								ft_isalpha(int argument);
int								ft_isascii(int arg);
int								ft_isdigit(int arg);
int								ft_isprint(int arg);
char							*ft_itoa(int n);
void							ft_memdel(void **st);
char							*ft_strcat
(char *restrict etr, const char *restrict s2);
void							ft_strclr(char *s);
int								ft_strcmp(const char *s1, const char *s2);
char							*ft_strcpy(char *dest, const char *src);
void							ft_strdel(char **as);
int								ft_strequ(char const *s1, char const *s2);
void							ft_striter(char *s, void (*f)(char*));
void							ft_striteri
(char *s, void (*f)(unsigned int, char *));
size_t							ft_strlen(const char *str);
char							*ft_strmap(char const *str, char (*f)(char));
char							*ft_strmapi
(char const *str, char (*f)(unsigned int i, char c));
char							*ft_strncat
(char *restrict str, const char *restrict str2, size_t nb);
int								ft_strncmp
(const char *str, const char *s2, size_t n);
char							*ft_strncpy
(char *dest, const char *str, size_t nb);
int								ft_strnequ(char *s1, char *s2, size_t n);
char							**ft_strsplit(char const *s, char c);
char							*ft_strtrim(char const *s);
char							*ft_strnew(size_t size);
char							*ft_strsub(char const *s, unsigned int start,
		size_t len);
int								ft_tolower(int arg);
char							*ft_strdup(const char *str);
size_t							ft_strlcat
(char *restrict dst, const char *restrict src, size_t size);
void							ft_putstr_plus(char *str, char *str2);
char							*ft_pathjoin(char *path, char *dossier);

void							ft_printf(char *format, ...);
int								search_format(char *format, va_list ap);
int								print_type_lower1
(uint type_lower, uint flag, va_list ap);
int								print_type_lower2
(uint type_lower, uint flag, va_list ap);
int								print_type_lower3
(uint type_lower, uint flag, va_list ap);
int								print_type_upper1
(uint type_upper, uint flag, va_list ap);
int								print_point_adress
(uint type_lower, uint flag, va_list ap);
void							put_cast(t_vars vars, uint flag);
void							put_cast_ui(t_vars vars, uint flag);
uint							get_flag(char *format);
void							*ft_mmalloc(size_t size);
char							*ft_tabtostr(char **tab);
char							**ft_delfromtab(char **tab, int index);
int								ft_existintab(char **tab, char *str);

#endif
