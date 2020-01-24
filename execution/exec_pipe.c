/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 21:40:41 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/20 11:12:03 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void    change_cmd(char **cmd, int red_type)
{
    free(*cmd);
    if (red_type & READ_FILE)
        *cmd = ft_strdup("more");
    else
        *cmd = ft_strdup("cat");
}

int     exec_lstpipe(t_parse *lst, char **env)
{
    int pip[2];
    int oldpipe_r;
    int pgrp;
    int proc_nbr = 0;
    char **argv;
    int background = lst->bg;

    pgrp = 0;
    while (lst)
    {
        if (!lst->cmd[0] || !lst->cmd[ft_skip_sep(lst->cmd, " \t\n")])
            change_cmd(&lst->cmd, lst->lst_reder_aggr->red_type);
        if (lst->pipe || proc_nbr > 0)
            pipe(pip);
        if (!(lst->pid = fork()))
            child_job(lst, env, pip, oldpipe_r, proc_nbr);
        else if (lst->pid == -1)
            return (ft_perror("42sh: fork"));
        if (lst->pipe || proc_nbr > 0)
			close(pip[1]);
        if (proc_nbr != 0)
            close(oldpipe_r);
        oldpipe_r = pip[0];
        if (proc_nbr == 0)
            pgrp = lst->pid;
        if (setpgid(lst->pid, pgrp) == -1)
            ft_perror("42sh: setpgid");
        if (proc_nbr == 0 && !background && control_gprocess(pgrp) == -1)
            ft_perror("42sh: tcsetpgid");
        proc_nbr++;
        lst = lst->pipe;
    }
    if (proc_nbr != 1)
        close(oldpipe_r);
    return (parent_job(pgrp, background));
}
