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
        if (objet->execution->pipe || !(status = is_abuiltin(objet, objet->execution->cmd, NULL, g_environ)))
            status = exec_lstpipe(objet->execution, g_environ);
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
