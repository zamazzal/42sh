/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 02:23:15 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/16 03:31:25 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSH_H
# define MYSH_H

# include "get_next_line.h"
# include "libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <pwd.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <dirent.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <ctype.h>
# include <termcap.h>

# define L_PIPE 1
# define L_SQ 2
# define L_DQ 3
# define L_HDC 4
# define L_B 5
# define L_CMDAND 6
# define L_CMDOR 7

# define BQ 1
# define SQ 2
# define DQ 4
# define IS_BRACKT 8
# define IS_CBRACKT 16

# define NONE 0
# define MINCE 1
# define PLUS 2
# define INTEROGATION 3
# define EQUAL 4
# define START_HASH 5
# define MODULO 6
# define TWO_MODULO 7
# define END_HASH 8
# define TWO_HASH 9
# define ERROR -1
# define ERROR_STOP -2
# define TRUE   1
# define FALSE  0
# define ALN "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789?"
# define SAFE(expr) if (!(expr)) return (0)

# define FLAGS_L 2048
# define FLAGS_R 131072
# define FLAGS_S 262144
# define FLAGS_P 32768

# define IS_BACKGROUND 1
# define IS_SUSPEND 2
# define IS_FOREGROUND  8
# define IS_SELECTED 4
# define JOBS_ID 1
# define JOBS_CUR 2
# define JOBS_MODE 4
# define JOBS_CMD 8
# define JOBS_PGID 16
# define JOBS_ALLCMD 32
# define JOBS_BG     64
# define JOBS_PID    128
# define JOBS_STAT  256

# define HTABLE_SIZE 1000000
# define PARSING_H
# define PIPE 0x01
# define AND 0x02
# define OUR 0x04
# define SEP 0x08
# define BG 0x010

# define RED_AGGR 0x06
# define ALL_READ_TYPE  0x01C
# define ALL_PRINT_TYPE 0x03
# define HERE_STRING 1
# define HERE_DOC 2
# define TRUNC_TF 8
# define APPEN_TF 16
# define RDWR_TF 32
# define SWAP_LFD_TRFD 64
# define READ_FILE 128
# define READ_FCUSFD 256

# define REDR_STIN_STOUT 512
# define CLOSE_LFD 4
# define CLOSE_RFD 1024

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

typedef struct s_jobs			t_jobs;
typedef struct s_parse			t_parse;
typedef struct s_redirections	t_redirections;
typedef struct s_utils			t_utils;

struct							s_jobs
{
	t_parse	*node_cmd;
	int		proc_id;
	size_t	mode;
	pid_t	pgid;
	t_jobs	*next;
};

struct							s_parse
{
	char			*cmd;
	int				bg;
	int				pid;
	char			*path;
	t_redirections	*lst_reder_aggr;
	t_parse			*if_fail;
	t_parse			*if_seccess;
	t_parse			*pipe;
	t_parse			*next;
};

struct							s_redirections
{
	char			*file_name;
	int				right_fd;
	int				left_fd;
	int				red_type;
	t_redirections	*next;
};

struct							s_utils
{
	char	*cmd;
	char	*arg;
	size_t	index_arg;
	size_t	end_argument;
};

typedef struct					s_exec_objet
{
	int	pip[2];
	int	old_ppr;
	int	pgrp;
	int	bg;
	int	proc_nbr;
	int	builtin_exit;
}								t_exec_objet;

typedef struct					s_hashtable
{
	int					hits;
	char				*cmd;
	char				*content;
}								t_hashtable;

typedef	struct					s_read
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
}								t_read;

int			g_exec_fc;
char		**g_environ;
t_jobs		*g_jobs;
t_jobs		*g_current_jobs;
int			g_last_jobs_id;
pid_t		g_shell_pid;
int			g_tmpmode;
char		**g_tmpenv;
char		**g_tmpintern;
t_read		*g_insert;
t_read		*g_readline;
pid_t		g_pid_cmd;
int			g_ctrl_dsig;
int			g_ctrl_csig;
char		**g_environ;
char		**g_intern;
char		*g_ttyname;
char		*g_pwd;
char		**g_all_aliases;
int			g_line_type;
t_hashtable	*g_htable[HTABLE_SIZE];
char		*g_random_save;
char		*g_history_saved;

t_jobs							*get_jobsid(t_jobs *jobs
, t_jobs **previous, int job_id);
int								get_exit_status(int status);
int								control_gprocess(int gpid);
char							**ms_parse(char *line);
int								validate_arg(char *arg, ushort type);
int								proc_substitution_w(char *cmd
, char **cal_cmd);
int								proc_substitution_r(char *cmd, int pip[2]
, char **cal_cmd);
int								get_option(char **argv, int *option);
int								get_right_side(t_utils *utils
, size_t *end, char **right_side);
int								ft_seter(char *str);
int								check_var_ster(char *str);
int								ft_exportone(char *str);
int								check_identifier(char *str);
int								ft_getexported(void);
int								ft_getexported_one(char **argv);
int								ft_notvalid(char *str);
int								nextisvar(char *var, char c);
int								ft_check_var_temp(int argc, char **argv);
char							*ft_strojoin(char **s1, char *s2
, int overwrite);
char							*ft_strappend(char **a_s1, char c
, int overwrite);
void							join_rest_tocmd(char *arg
, size_t start, size_t end);
void							read_herdoc(char **her_doc);
int								check_lfd(char *ptr);
char							**ft_check_all(char **arg);
int								parse_cmd(t_parse **lst, t_utils *utils);
int								init_end_parse(char **cmd, t_parse **lst
, t_utils **utils, int mode);
void							delete_node(t_jobs *node);
int								point_final_node(t_parse **parse);
int								ft_notfound(char *cmd);
char							*ft_getpath(char *cmd);
int								set_cmd(t_parse *ptr);
int								ft_check_s(char **arg);
int								ft_check_s1(char **arg);
int								ft_check_args1(char **arg);
int								ft_check_args2(char **arg, int i);
int								ft_check_e(char **arg, int i);
int								ft_check_args3(char **arg, int i);
void							ft_clear_file(void);
int								ft_arg1(char **arg, int i);
int								ft_endoftmp(int val);
int								ft_settmpvar(char **cmd);
unsigned long					hash_calc(char *str);
void							ret_tab_toline(char *line);
int								type_error(char *str, int ret);
int								if_hashed(char *cmd, int flag);
char							*ft_checkifhashed(char *cmd);
int								if_alias(char *str, int flag);
char							*ft_getalias(char *key);
int								ft_return(int r);
int								ft_type_error(char *s1, char *s2);
int								ft_test(char *name, char *flag);
int								ft_test3args(char **argv);
int								ft_fc_built(char **args, char **line);
void							ft_cpythevalue(char **tobereplaced
, char *value, int start);
char							*ft_changevalue(char *value, char *alias_value,
								int len_tobereplaced);
char							*ft_delquote(char *value);
char							*ft_addquote(char *arg);
int								setervars(char **argv);
int								ft_exit(char **args);
void							ft_setstatus_var(int status);
int								alias(char **arg, char ***all_aliases);
int								unalias(char **arg, char ***all_aliases);
int								ft_parameters(char **param_arg);
void							ft_replacealiass(char **line
, char **allaliases);
int								ft_lentoequal(char *alias_arg);
char							*ft_addquote(char *arg);
void							ft_putaliases(char **all_aliases, int index);
int								ft_aliasexist(char *alias, char **all_aliases);
int								ft_aliasoption(char *arg);
void							ft_addalias(char *alias_arg
, char ***all_aliases);
int								ft_unaliasoption(char *arg);
char							*ft_getaliasvalue(char *arg, char **all_aliases,
									char ***loopdetector);
void							ft_badsubstitution(char *param_arg
, int *tag);
int								ft_badsubstitutiondetector(char *param
, int *tag);
void							ft_normalvalue(char **param_arg, int *tag);
int								ft_tagindex(char *param_arg, int *tag);
int								ft_issetornull(char *variablename,
							int tag, char **arg);
void							ft_splitytags(char **splitted
, int *tag, char **arg);
void							ft_hashmodulus(char **splitted
, int *tag, char **arg);
void							ft_starthash(char **arg, int *tag);
char							**ft_splittotwo(char *param_arg, int tag);
int								ft_expand(char *line, int *i, char **result);
int								cut_if_redoraggr(t_redirections **red_aggr
, t_utils *utils);
int								ms_expand_dollar(char **buffer, char *arg);
void							ms_set_quote(int *quoted, char *quote, char c);
void							free_lstour(t_parse **lst);
void							ft_freeh_htab(void);
int								ft_add_inhashtable(char *cmd, char *path);
char							*ft_getcmd_from_htab(char *cmd);
int								ft_htab_addhit(char *cmd);
void							ft_freeh_htab(void);
int								ft_hash(int argc, char **argv);
char							*ft_checkcmd(char *cmd);
char							**clear_quots(char **argv);
int								ft_set(void);
int								ft_unset(int argc, char **argv);
int								test(int argc, char **argv);
int								ft_export(int argc, char **argv);
int								add_argument(t_parse **lst, t_utils *utils);
int								is_abuiltin(t_parse *lst, char **argv
, int *builtin_exit);
int								exec_redirection(t_redirections *rederction
, char **cal_cmd);
void							inform_user(t_jobs *node, int stat, int info);
void							if_jobsexited(int status, t_jobs *nod);
char							**ft_cmdsplit(char *ptr, int c);
void							exec_lstparse(t_parse *lst, int mode);
void							print_command(t_parse *lst);
void							check_lstjobs(void);
int								ft_seter2(char *str);
int								bg_builtin(char **argv);
int								fg_builtin(char **argv);
int								jobs_builtin(char **argv);
int								if_background(int pgid
, t_parse *execution, t_jobs *ptr);
int								if_suspend(int status, int pgid
, t_parse *execution, t_jobs *ptr);
int								if_signaled(int status);
void							sig_handl(int sig);
void							sig_init(void);
int								exec_lstpipe(t_parse *lst, int mode);
int								ft_perror(char *message);
char							*get_path_cmd(char *cmd);
void							child_job(t_parse *lst, int pip[2]
, int oldpr, int proc_nbr);
int								parent_job(int child_pid, int bg
, t_parse *execution);
void							print_command_p(t_parse *lst);
int								ft_builtins(char **av);
int								ft_echo(char **args);
int								ft_type(char **args);
int								ft_type_options(int *opt
, int *place, char **args);
char							*access_file(char **env, char *file);
int								if_builtin(char *str);
int								ft_cd_options(int *opt
, int *place, char **args);
int								ft_cd(char **args);
char							*mod_path(char *path);
char							*mod_point(char *path);
char							*get_all_path(char *path);
char							*get_cdpath(char *pwd, char *path);
void							replace_alias(char **line);
char							*ms_expand_quotes(char *arg);
char							*ms_expand_tilde(char *arg);
char							*ms_expand_dollars(int *ret, char *arg);
int								ft_true(void);
int								ft_false(void);
char							**save_last_herdoc(char **last_herdoc
, int mode);
char							*ft_strndup_shell(char *cmd, size_t n);
int								redirec_isnear(ushort type);
int								is_background(t_parse **parse, t_parse *lst);
size_t							if_redoraggr(t_redirections **redirec_aggre
, t_utils *utils);
void							complet_type(char **cmd, ushort dernier_type);
t_parse							*exit_parsing(t_parse **lst
, t_utils **utils, ushort exit);
t_parse							*parse_lst(char **cmd);
int								is_near(ushort type);
char							*get_next_arg(char **cmd, size_t *index);
int								ft_strchr_index_shell(char *cmd, char c);
void							argument_join(char **cmd, char *argument);
int								change_to_opand(t_parse **parse, t_parse *lst);
int								change_to_seperat(t_parse **parse
, t_parse *lst);
int								change_to_opor(t_parse **parse, t_parse *lst);
int								ft_check_eq(char *str);
int								change_to_pipe(t_parse **parse);
int								type_of_argument(const char *arg, size_t i);
int								ft_tablen(char **array);
char							**ft_tabdup(char **array);
int								ft_setitern(char *name, char *content);
char							*ft_getenv(const char *name);
char							**ft_jointab(char **tab1, char **tab2);
char							*ft_getvalue(char *str);
char							*ft_getkey(char *str);
int								ft_setenv(char *name, char *content);
void							ft_freetable(char ***array);
void							ft_puttables(char **table);
char							*ft_getintern(const char *name);
int								ft_getcpos(char *str, int c);
char							*ft_makevar(char *key, char *value);
int								ft_checkcinstr(char *ptr, int c);
int								ft_strinstr(const char *s1
, const char *s2, int len);
char							*ft_strjoin_lite(char *s1, char const *s2);
char							**ft_addtotab_var(char **tabl, char *str);
int								checkbackslash(char *ptr, int i);
char							*ft_readline(char *prompt);
void							ft_setting();
void							ft_cannonical_mod(void);
void							ft_setterm();
int								ft_key_detect(char *key);
void							ft_addtoline(char *key);
void							ft_do_termcap(char *termcap);
int								ft_totaly_count();
int								ft_curlinelen(int liney);
void							ft_movecursor_right();
void							ft_defult_term();
void							ft_movecursor_left(char *key);
void							ft_delete_char(char *key);
int								ft_totaly_count();
void							ft_cursor_lastpos();
void							ft_remove_line();
void							ft_movecursor_down();
void							ft_movecursor_up();
void							ft_movecursor_back_word(char *key);
void							ft_movecursor_next_word();
void							ft_movestart();
void							ft_moveend();
void							ft_copy(char *key);
void							ft_cut(char *key);
void							ft_history_back();
void							ft_history_forwad();
void							ft_add_history(char **line);
void							ft_delete_onechar();
void							sigint_handler(int sig);
void							ft_clear_screen();
void							ft_syncwin_size();
void							sigwinch_handler(int sig);
void							ft_signal_handler(t_read *g_insert);
void							ft_cannonical_mod();
void							prompt();
void							ft_setting1();
void							ft_puttab();
int								calc_tab(int index);
void							replace_tab();
void							ft_savein_file(char *line);
void							ft_load_history();
void							ft_history_expansions();
char							*ft_replace(char *line
, char *src, char *to_rep);
void							ft_search_hist();
void							ft_execute_editor(void);
int								ft_check_flag(void);
void							ft_hist_e(void);
void							ft_hist_er(void);
int								ft_arg_nbr(char **arg);
void							ft_clear_file(void);
int								ft_check_args(char **arg);
void							ft_moveleft_tab(char *buf);
void							ft_movecursor_tab(void);
void							ft_movecursor_left1(char *buf);
int								ft_totaly_count(void);
int								ft_curlinelen(int liney);
int								countbigy(char *buf);
int								ft_totaly_count(void);
int								ft_fornor(void);
int								ft_formove(void);
int								ft_deletemulti(void);
int								add_to(char *line, int i);
char							*ft_charjoin(char *str, char c);
void							ft_puttab(void);
void							ft_putspace(int num);
void							ft_count_tab(int *x, int tabu, int *y);
char							*ft_join(char *dest, char *src, int *j);
int								expansion_num(char *str, int i);
int								expansion_word(int i, char *line);
int								get_hist_num(char *arg);
int								ft_arg(char **arg, int i);
void							useless(int *x, int *y);
void							useless2(int index, int *x);
void							useless3(int *x, int *y);
int								ft_check_editor(char *arg);
void							ft_initialize_fc(void);
int								list_error4(void);
int								list_error3(void);
int								list_error2(void);
int								list_error1(void);
int								restore_filds(void);
int								ft_init(t_parse *lst, char *fc);
char							*ft_ret(char *line, char **tmp);
#endif
