/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:39:04 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 18:41:08 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

t_jobs			*get_jobsid(t_jobs *jobs, t_jobs **previous, int job_id)
{
	if (!jobs)
		return (NULL);
	if ((int)jobs->proc_id == job_id)
		return (jobs);
	if (previous)
		*previous = jobs;
	return (get_jobsid(jobs->next, previous, job_id));
}

static t_jobs	*get_specif_node(char **argv, t_jobs *jobs)
{
	t_jobs *node;

	node = NULL;
	if ((getpid() != g_shell_pid))
	{
		ft_putendl_fd("42sh: fg: no job control.", 2);
		return (NULL);
	}
	if (argv[1] && !(node = get_jobsid(jobs, NULL, ft_atoi(argv[1]))))
	{
		ft_putstr_fd("42sh: fg: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": no such job.", 2);
		return (NULL);
	}
	if (!jobs)
	{
		ft_putendl_fd("42sh: fg: current: no such job.", 2);
		return (NULL);
	}
	if (!node && !(node = g_current_jobs))
		node = jobs;
	return (node);
}

int				fg_builtin(char **argv)
{
	t_jobs	*jobs;
	int		status;

	if (!(jobs = get_specif_node(argv, g_jobs)))
		return (1);
	jobs->mode &= ~(IS_SUSPEND | IS_BACKGROUND);
	jobs->mode |= (IS_FOREGROUND);
	inform_user(jobs, 0, JOBS_ID | JOBS_CUR | JOBS_MODE | JOBS_PGID | JOBS_CMD);
	ft_putchar('\n');
	signal(SIGCHLD, NULL);
	control_gprocess(jobs->pgid);
	if (kill(jobs->pgid * -1, SIGCONT) == -1)
		return (ft_perror("42sh: kill"));
	if ((status = parent_job(jobs->pgid, 0, jobs->node_cmd)) == -1)
		return (-1);
	if (WIFEXITED(status) || WIFSIGNALED(status))
		if_jobsexited(status, jobs);
	signal(SIGCHLD, sig_handl);
	return (get_exit_status(status));
}
