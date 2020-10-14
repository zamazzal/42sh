/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:22:37 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 18:40:54 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	point_var(char **arg, t_jobs **ptr, size_t *flag)
{
	if ((getpid() != g_shell_pid))
	{
		ft_putendl_fd("42sh: bg: no job control.", 2);
		return (1);
	}
	if (!arg[1] && !g_current_jobs && !g_jobs)
	{
		ft_putendl_fd("42sh: bg: current no such.", 2);
		return (1);
	}
	else if ((arg[1] && ((*flag) = 1))
	|| (!arg[1] && !(*ptr = g_current_jobs)))
		*ptr = g_jobs;
	return (0);
}

static int	jobs_to_bg(t_jobs *jobs)
{
	if (!jobs)
		return (-1);
	inform_user(jobs, 0, JOBS_ID | JOBS_CUR | JOBS_PGID | JOBS_ALLCMD);
	ft_putchar('\n');
	if (kill(jobs->pgid * -1, SIGCONT) == -1)
		return (ft_perror("42sh: kill"));
	jobs->mode &= ~(IS_SUSPEND);
	jobs->mode |= IS_BACKGROUND;
	return (1);
}

static int	check_arg(char *arg, t_jobs **ptr)
{
	if (*ptr && (int)(*ptr)->proc_id == ft_atoi(arg))
	{
		jobs_to_bg(*ptr);
		*ptr = g_jobs;
		return (0);
	}
	else if (!*ptr || !(*ptr = (*ptr)->next))
	{
		ft_putstr_fd("42sh: bg: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": no such job.", 2);
		*ptr = g_jobs;
		return (0);
	}
	return (1);
}

int			bg_builtin(char **argv)
{
	t_jobs *jobs;
	size_t flag;
	size_t i;

	flag = 0;
	i = 1;
	jobs = NULL;
	if (point_var(argv, &jobs, &flag))
		return (1);
	if (!flag)
		jobs_to_bg(jobs);
	else
		while (argv[i])
			if (!check_arg(argv[i], &jobs))
				i++;
	return (0);
}
