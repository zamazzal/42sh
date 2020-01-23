/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:18:23 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/22 17:25:59 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"


int     is_abuiltin(t_objet *objet, char *cmd, char **argv, char **environ)
{
    int exit_status;

    if (!ft_strncmp(cmd, "jobs", 4))
        exit_status = jobs_builtin(ft_strsplit(cmd, ' '), objet);
    else if (!ft_strncmp(cmd, "fg", 2))
        exit_status = fg_builtin(ft_strsplit(cmd, ' '), objet);
    else if (!ft_strncmp(cmd, "bg", 2))
        exit_status = bg_builtin(ft_strsplit(cmd, ' '), objet);
    else
        return (0);
    // else if (ft_builtins(argv) != -1)
    //     return (1);
    // set exit status 
    return (1);
}

void    exec_lstparse(t_objet *objet)
{
    t_parse *lst;
    int fd;
    int     status;

    lst = objet->lst_parse;
    objet->execution = lst;
    while (objet->execution)
    {
        if (objet->execution->pipe || !(status = is_abuiltin(objet, objet->execution->cmd, NULL, objet->environ)))
            status = exec_lstpipe(objet->execution, objet->environ);
        if ((WIFSIGNALED(status) || WIFSTOPPED(status) || (WIFEXITED(status) && WEXITSTATUS(status) != 0)) && objet->execution->if_fail)
            objet->execution = objet->execution->if_fail;
        else if (WIFEXITED(status) && WEXITSTATUS(status) == 0 && objet->execution->if_seccess)
            objet->execution = objet->execution->if_seccess;
        else
        {
            lst = lst->next;
            objet->execution = lst;   
        }
        objet->exec_mode = 0;
    }
}

#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/get_next_line.h"

int main()
{
    t_objet     **objet;
    extern char **environ;
    char        *line;
    char        *tmp;

    sig_init();
    objet = save_objet();
    if (!(*objet = (t_objet*)ft_memalloc(sizeof(t_objet))))
        return (ft_perror("42sh: malloc"));
    (*objet)->environ = environ;
    while (1)
    {
        if ((line = readline("\033[1;36m42sh$> \033[0m")) > 0)
		{
            tmp = line;
            line = ft_strtrim(line);
            free(tmp);
            if (!ft_strncmp(line, "exit", 4))
            {
                free(line);
                return (0);
            }
            if (((*objet)->lst_parse = parse_lst(line)))
                exec_lstparse(*objet);
        }
        ft_strdel(&line);
        exit_parsing(&(*objet)->lst_parse , NULL, EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
