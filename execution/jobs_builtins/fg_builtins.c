/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 14:03:51 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/18 17:45:42 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int     fg_builtin(char **av, t_objet *objet)
{
    t_jobs *node;

    node = NULL;
    if (!objet)
    {
        ft_putendl_fd("42sh: fg: no job control", 2);
        return (1);//FAILURE
    }
    if (av[1] && av[1][0] == '-')
    {
        ft_putendl_fd("42sh: fg: usage: fg [job_spec]", 2);
        return (1);// FAILURE
    }
    if (av[1])
        if (!(node = get_jobs_nbr(av[1], objet->lst_jobs)))
            return (1);//FAILURE
    if (!objet->lst_jobs)
    {
        ft_putstr_fd("42sh: fg: current: no such job", 2);
        return (1);//FAILURE
    }
    if (!node)
        node = get_current_job(objet->lst_jobs);
    ft_putendl(node->cmd);
    if (control_gprocess(node->pid) == -1)
        return (1);//FAILURE
    kill(SIGCONT, node->pid);
    waitpid()
}