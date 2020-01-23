/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_bg_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:49:22 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/22 17:35:39 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

t_jobs *get_jobsid(t_jobs *jobs, t_jobs **previous, int job_id)
{
    if (!jobs)
        return (NULL);
    if (jobs->proc_id == job_id)
        return (jobs);
    *previous = jobs;
    return (get_jobsid(jobs->next, previous, job_id));
}

int    fg_builtin(char **argv, t_objet *obj)
{
    t_jobs *jobs;
    t_jobs *previous;
    int status;

    jobs = NULL;
    previous = NULL;
    if (argv[1] && !(jobs = get_jobsid(obj->lst_jobs, &previous, ft_atoi(argv[1]))))
    {
        ft_putstr_fd("42sh: fg: ", 2);
        ft_putstr_fd(argv[1], 2);
        ft_putendl_fd(": no such job.", 2);
        return (1);//failure
    }
    if (!obj->lst_jobs)
    {
        ft_putendl_fd("42sh: fg: current: no such job.", 2);
        return (1);//failure
    }
    if (!jobs && (jobs = obj->lst_jobs))
        while (jobs && !(jobs->mode & IS_SELECTED) && jobs->next && (previous = jobs))
            jobs = jobs->next;
    ft_putnbr(jobs->pgid);
    ft_putstr(" continued\t");
    print_command(jobs->node_cmd);
    if (control_gprocess(jobs->pgid) == -1)
        return (ft_perror("42sh: tcsetpgrp"));
    signal(SIGCHLD, SIG_IGN);
    kill(jobs->pgid, SIGCONT);
    while (waitpid(jobs->pgid * -1, &status, WUNTRACED) > 0)
        if (WIFSTOPPED(status))
            break ;
    if (control_gprocess(getpgrp()) == -1)
        return (ft_perror("42sh: tcsetpgrp"));
    if (WIFSTOPPED(status))
    {
        ft_putchar('[');
        ft_putnbr(jobs->proc_id);
        ft_putchar(']');
        (jobs->mode & IS_SELECTED) > 0 ? ft_putstr("+ ") : ft_putstr("- ");
        ft_putnbr(jobs->pgid);
        ft_putstr("\t\t");
        print_command(jobs->node_cmd);
        jobs->mode &= ~(IS_BACKGROUND);
        jobs->mode |= IS_SUSPEND;
    }
    else
    {
        if_signaled(status);
        if (previous)
            previous->next = jobs->next;
        else
            obj->lst_jobs = jobs->next;
        exit_parsing(&jobs->node_cmd, NULL, EXIT_FAILURE);
        free(jobs);
    }
    signal(SIGCHLD, sig_handl);
    return (0);// SECCESS
}

int     bg_builtin(char **argv, t_objet *obj)
{
    t_jobs *jobs;
    t_jobs *previous;

    previous = NULL;
    jobs = NULL;
    if (argv[1] && !(jobs = get_jobsid(obj->lst_jobs, &previous, ft_atoi(argv[1]))))
    {
        ft_putstr_fd("42sh: bg: ", 2);
        ft_putstr_fd(argv[1], 2);
        ft_putendl_fd(": no such job.", 2);
        return (1);
    }
    else if (!(obj->lst_jobs))
    {
        ft_putendl_fd("42sh: bg: current: no such", 2);
        return (1);
    }
    if (!jobs && (jobs = obj->lst_jobs))
        while (jobs && jobs->next && (jobs->mode & IS_SELECTED))
            jobs = jobs->next;
    ft_putchar('[');
    ft_putnbr(jobs->proc_id);
    ft_putchar(']');
    ft_putstr(" ");
    ft_putnbr(jobs->pgid);
    ft_putstr("\t");
    print_command(jobs->node_cmd);
    ft_putendl(" &");
    kill(jobs->pgid, SIGCONT);
    jobs->mode &= ~(IS_SUSPEND);
    jobs->mode |= IS_BACKGROUND;
    return (0);
}