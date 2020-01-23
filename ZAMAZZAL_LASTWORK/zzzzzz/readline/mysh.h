#ifndef MYSH_H
# define MYSH_H
int				ft_tablen(char **array);
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <sys/wait.h>
# include <ctype.h>
# include <termcap.h>
# include <fcntl.h>
# include "libft.h"

# define BUFF_SIZE 4000
# define LINE_MAX  200000
# define ENTER_KEY 10
# define MOVE_RIGHT (key[2] == 67 && key[1] == 91 && key[0] == 27)
# define MOVE_LEFT (key[2] == 68 && key[1] == 91 && key[0] == 27)
# define MOVE_UP (key[3] == 65 && key[2] == 91 && key[1] == 27 && key[0] == 27)
# define MV_DWN (key[3] == 66 && key[2] == 91 && key[1] == 27 &&  key[0] == 27)
# define MOVE_START (key[2] == 72 && key[1] == 91 && key[0] == 27)
# define MOVE_END (key[2] == 70 && key[1] == 91 && key[0] == 27)
# define MV_NEXT (key[3] == 67 && key[2] == 91 && key[1] == 27 && key[0] == 27)
# define MV_BACK (key[3] == 68 && key[2] == 91 && key[1] == 27 && key[0] == 27)
# define PAST (key[0] == 16)
# define COPY (key[0] == 21)
# define TAB (key[0] == 9)
# define COPY3 (key[0] == 12)
# define COPY2 (key[0] == 9)
# define CUT (key[0] == 24)
# define CUT1 (key[0] == 2)
# define CUT2 (key[0] == 14)
# define DELETE (key[0] == 127)
# define DELETE_LINE (key[0] == 18)
# define HISTORY_MOVE_BACK (key[2] == 65 && key[1] == 91 && key[0] == 27)
# define HISTORY_MOVE_NEXT (key[2] == 66 && key[1] == 91 && key[0] == 27)
# define CURSOR_UP  "up"
# define CURSOR_DOWN "sf"
# define CURSOR_RIGHT "nd"
# define CURSOR_LEFT "le"
# define CURSOR_CORNER "cr"
# define DELETE_AFTER_CURSOR "cd"

/*
**		Malloc Protection
*/

# define SAFE(expr) if (!(expr)) return (0)



typedef	struct	s_read
{
	char	*line;
	char	*topast;
	int		winsize;
	int		linelen;
	int		linex;
	int		liney;
	int		tmplinex;
	int		tmpliney;
	int		curlinelen;
	int		totaly;
	int		index;
	int		info;
	char	**history;
	int		indexfor_history;
	int		is_quote;
	int		a;
	int		history_search;
	int		is_tab;
	int		tab_calc;
	int		tab_while;
	int		lst_ps;
	int		r;
	int		e;
	char	*editor;
	int		n;
	int		l;
	int		num1;
	int		num2;
	int		file_fd;

}				t_read;

t_read			*g_insert;
t_read			*g_readline;
pid_t			g_pid_cmd;

int				g_herdoc_sig;
int				g_ctrl_dsig;
int				g_is_pipe;

// vars
char			**g_environ;
char			**g_intern;


char	**ft_tabdup(char **array);
int		ft_setitern(char *name, char *content);
char			*ft_getenv(const char *name);
char			**ft_jointab(char **tab1, char **tab2);

char	*ft_getvalue(char *str);
char	*ft_getkey(char *str);
int		ft_setenv(char *name, char *content);
void	ft_freetable(char ***array);
void	ft_puttables(char **table);
char			*ft_getintern(const char *name);
int		ft_getcpos(char *str, int c);
char	*ft_makevar(char *key, char *value);
int		ft_checkcinstr(char *ptr, int c);
int		ft_strinstr(const char *s1, const char *s2, int len);
char	*ft_strjoin_lite(char *s1, char const *s2);
char		**ft_addtotab_var(char **tabl, char *str);
int				checkbackslash(char *ptr, int i);


/////////
// add readline

char	*ft_readline(char *prompt);



/////////
void			ft_setting();
void			ft_cannonical_mod(void);
void			ft_setterm();
int				ft_key_detect(char *key);
void			ft_addtoline(char *key);
void			ft_do_termcap(char *termcap);
int				ft_totaly_count();
int				ft_curlinelen(int liney);
void			ft_movecursor_right();
void			ft_defult_term();
void			ft_movecursor_left(char *key);
void			ft_delete_char(char *key);
int				ft_totaly_count();
void			ft_cursor_lastpos();
void			ft_remove_line();
void			ft_movecursor_down();
void			ft_movecursor_up();
void			ft_movecursor_back_word(char *key);
void			ft_movecursor_next_word();
void			ft_movestart();
void			ft_moveend();
void			ft_copy(char *key);
void			ft_cut(char *key);
void			ft_history_back();
void			ft_history_forwad();
void			ft_add_history(char **line);
void			ft_delete_onechar();
void			sigint_handler(int sig);
void			ft_clear_screen();
void			ft_syncwin_size();
void			sigwinch_handler(int sig);
void			ft_signal_handler(t_read *g_insert);
void			ft_cannonical_mod();
void			prompt();
void			ft_setting1();
void			ft_puttab();
int				calc_tab(int index);
void			replace_tab();
void			ft_savein_file(char *line);
void			ft_load_history();
void			ft_history_expansions();
void			ft_search_hist();
void			ft_fc_built();
void			ft_execute_editor(void);
int				ft_check_flag(void);
void			ft_hist_e(void);
void			ft_hist_er(void);
int				ft_arg_nbr(char **arg);
void			ft_clear_file(void);
int				ft_check_args(char **arg);
void			ft_moveleft_tab(char *buf);
void			ft_movecursor_tab(void);
void			ft_movecursor_left1(char *buf);
int				ft_totaly_count(void);
int				ft_curlinelen(int liney);
int				countbigy(char *buf);
int				ft_totaly_count(void);
int				ft_fornor(void);
int				ft_formove(void);
int				ft_deletemulti(void);
int				add_to(char *line, int i);
char			*ft_charjoin(char *str, char c);
void			ft_puttab(void);
void			ft_putspace(int num);
void			ft_count_tab(int *x, int tabu, int *y);
char			*ft_join(char *dest, char *src, int *j);
int				expansion_num(char *str, int i);
int				expansion_word(int i, char *line);

#endif