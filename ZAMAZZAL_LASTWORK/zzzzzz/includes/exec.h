/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 02:23:15 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/22 17:26:37 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "../includes/parsing.h"
# include "../includes/get_next_line.h"
# include "../builtins/builtins.h"
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#define TRUE   1
#define FALSE  0

# define ALNUM "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789"
# define SAFE(expr) if (!(expr)) return (0)

# define FLAGS_L 2048
# define FLAGS_R 131072
# define FLAGS_S 262144
# define FLAGS_P 32768
# define IS_BACKGROUND 0x01
# define IS_SUSPEND 0x02
# define IS_SELECTED 0x04

typedef struct s_jobs t_jobs;
typedef struct s_objet t_objet;

char		**ms_parse(char *line);

struct s_jobs
{
    t_parse *node_cmd;
//  char    *cmd;
    size_t  proc_id;
    size_t  mode;
    pid_t   pgid;
    t_jobs  *next;
};

struct s_objet
{
    t_parse *lst_parse;
  //  t_parse *lst_parse_bg_or_susp;
    t_parse *execution;
    t_jobs  *lst_jobs;
    char    **environ;
    int     exec_mode;
};
char			**ft_cmdsplit(char *ptr, int c);


//jobs controle
void    exec_lstparse(t_objet *objet);
void    print_command(t_parse *lst);
int     bg_builtin(char **argv, t_objet *obj);
void    check_lstjobs(t_objet *objet);
int     fg_builtin(char **argv, t_objet *obj);
int     jobs_builtin(char **argv, t_objet *objet);
int     if_background(int pgid);
int     if_suspend(int status, int pgid);
int     if_signaled(int status);

//signal
void    sig_handl(int sig);
void    sig_init(void);


int     exec_lstpipe(t_parse *lst, char **env);
t_parse *add_tosuspended_proc(t_objet *objet);
int     control_gprocess(int gpid);
t_objet **save_objet(void);
int     ft_perror(char *message);
char    *get_path_cmd(char *cmd, char **environ);
void    child_job(t_parse *lst, char **environ, int pip[2], int oldpr, int proc_nbr);
char    *ft_getenv(char **environ, char *var);
int     parent_job(int child_pid, int bg);

#endif 