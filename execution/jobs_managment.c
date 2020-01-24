/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 05:41:27 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/22 17:33:26 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static t_parse   *move_execution_node(t_objet *objet, t_parse **dest)
{
    if (!(*dest = (t_parse*)ft_memalloc(sizeof(t_parse))))
        return (NULL);
    (*dest)->cmd = objet->execution->cmd;
    objet->execution->cmd = NULL;
    (*dest)->if_fail = objet->execution->if_fail;
    objet->execution->if_fail = NULL;
    (*dest)->if_seccess = objet->execution->if_seccess;
    objet->execution->if_seccess = NULL;
    (*dest)->pipe = objet->execution->pipe;
    objet->execution->pipe = NULL;
    (*dest)->pid = objet->execution->pid;
    (*dest)->lst_reder_aggr = objet->execution->lst_reder_aggr;
    objet->execution->lst_reder_aggr = NULL;
    return (*dest);
}

int     if_suspend(int status, int pgid)
{
    t_objet *objet;
    t_jobs  **jobs;
    int     proc_nbr;

    proc_nbr = 1;
    if (WIFSTOPPED(status))
    {
        objet = *save_objet();
        jobs = &objet->lst_jobs;
        while (*jobs && ++proc_nbr)
        {
            (*jobs)->mode &= ~(IS_SELECTED);
            jobs = &(*jobs)->next;
        }
        if (!(*jobs = (t_jobs*)ft_memalloc(sizeof(t_jobs))))
            return (ft_perror("42sh: malloc"));
        (*jobs)->proc_id = proc_nbr;
        (*jobs)->pgid = pgid;
        (*jobs)->mode |= (IS_SUSPEND | IS_SELECTED);
        if (!((*jobs)->node_cmd = (t_parse*)ft_memalloc(sizeof(t_parse))))
            return (ft_perror("42sh: malloc"));
        (*jobs)->node_cmd->cmd = objet->execution->cmd;
        objet->execution->cmd = NULL;
        (*jobs)->node_cmd->lst_reder_aggr = objet->execution->lst_reder_aggr;
        objet->execution->lst_reder_aggr = NULL;
        (*jobs)->node_cmd->pipe = objet->execution->pipe;
        objet->execution->pipe = NULL;
        (*jobs)->node_cmd->pid = objet->execution->pid;
        ft_putchar('[');
        ft_putnbr(proc_nbr);
        ft_putchar(']');
        ft_putstr("+   Stopped\t\t");
        print_command((*jobs)->node_cmd);
        ft_putchar('\n');
        return (1);
    }
    return (0);
}

int     if_background(int pgid)
{
    int     proc_id;
    t_objet *objet;
    t_jobs **jobs;

    proc_id = 1;
    objet = *save_objet();
    jobs = &objet->lst_jobs;
    while ((*jobs) && proc_id++)
        jobs = &(*jobs)->next;
    if (!(*jobs = (t_jobs*)ft_memalloc(sizeof(t_jobs))))
        return (ft_perror("42sh: malloc"));
    (*jobs)->proc_id = proc_id;
    (*jobs)->mode = IS_BACKGROUND;
    (*jobs)->pgid = pgid;
    ft_putchar('[');
    ft_putnbr(((*jobs)->proc_id));
    ft_putchar(']');
    ft_putstr("-   \t\t");
    move_execution_node(objet, &(*jobs)->node_cmd);
    print_command((*jobs)->node_cmd);
    ft_putchar('\n');
    return (1);
}