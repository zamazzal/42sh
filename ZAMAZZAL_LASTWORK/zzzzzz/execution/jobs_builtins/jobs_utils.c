/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:23:55 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/18 17:33:37 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

t_jobs  *get_jobs_nbr(char *str, t_jobs *jobs)
{
    if (!jobs)
    {
        ft_putstr_fd("42sh: jobs: ", 2);
        ft_putstr_fd(str, 2);
        ft_putstr_fd("no such job.", 2);
        return (NULL);// fail
    }
    if ((ft_atoi(str) == jobs->proc_nbr) || !ft_strncmp(jobs->cmd, str, ft_strlen(str)))
        return (jobs);
    return (get_jobs_nbr(str, jobs->next));
}

t_jobs *get_current_job(t_jobs *jobs)
{
    if (!jobs)
        return (NULL);
    if (jobs->mode & IS_SELECTED)
        return (jobs);
    return (get_current_job(jobs->next));
}