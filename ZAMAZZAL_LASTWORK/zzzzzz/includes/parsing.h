/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:12:32 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/22 17:31:31 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../libft/libft.h"
#include <stdio.h>
# define PIPE 0x01 //1
# define AND 0x02 //2
# define OUR 0x04 //4
# define SEP 0x08 //8
# define BG 0x010 // 16
# define RED_AGGR 0x06//6
# define ALL_READ_TYPE  0x01C//28
# define ALL_PRINT_TYPE 0x03//3
# define READ_AND_WRITE_TO_FILE 0x0100//256 // <>
# define APP_TO_FILE 0x01//1             //0001// >> append file
# define PRINT_TO_FILE 0x02//2         //0010// > print output to filename
# define READ_FILE 0x04 //4            //100// < read filename
# define HERE_DOCUMENT 0x08//8         //1000// << EOF HERE DOCUMENT
# define PRINT_NEXT_STRING 0x010//16     //10000// <<< exmple : <<< "kokokook"
# define REDIRECT_STDIN_STDOUT 0x020//32 // &> || &>>
# define CLOSE_LFD 0x040//64              // close left fd
# define SWAP_LFD_T_RFD 0x080//128  // copy left fd to right fd

// 0010 0001
/// & in right == stdout and stderr
typedef struct s_parse t_parse;
typedef unsigned short t_ushort;
typedef struct s_redirections t_redirections;
typedef struct s_utils t_utils;

struct s_parse
{
    char    *cmd;
    int     bg;
    int     pid;
    t_redirections *lst_reder_aggr;//change here 1
    t_parse *if_fail;
    t_parse *if_seccess;
    t_parse *pipe;
    t_parse *next;
};

struct s_redirections
{
    char    *file_name;
    int     right_fd;
    int     left_fd;
    int     red_type;
    t_redirections *next;
};

struct s_utils
{
   // change here 2
    char    *cmd;
    char    *arg;
    size_t  index_arg;
    size_t  end_argument;
};

char    *ft_strndup_shell(char *cmd, size_t n);
int     redirec_isnear(t_ushort type);
int     is_background(t_parse **parse, t_parse *lst);
size_t  if_redoraggr(t_redirections **redirec_aggre, t_utils *utils);
void    complet_type(char **cmd, t_ushort dernier_type);
t_parse  *exit_parsing(t_parse **lst, t_utils **utils, t_ushort exit);
t_parse *parse_lst(char *cmd);
int     is_near(t_ushort type);
char    *stock_next_argument(char *cmd, size_t *end_argument, char **line_addr);
int      ft_strchr_index_shell(char *cmd, char c);
void    argument_join(char **cmd, char *argument);
int     change_to_opand(t_parse **parse, t_parse *lst);
int     change_to_seperat(t_parse **parse, t_parse *lst);
int     change_to_opor(t_parse **parse, t_parse *lst);
int     change_to_pipe(t_parse **parse);
int     type_of_argument(const char *arg, size_t i);
#endif
