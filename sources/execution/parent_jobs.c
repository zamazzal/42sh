/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 01:22:31 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/16 04:52:52 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	res_ign_ttin_ttou(int mode, int gpid)
{
	if (mode == 1 && gpid == getpgrp())
	{
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
	}
	else if (mode == 2 && gpid == getpgrp())
	{
		signal(SIGTTIN, NULL);
		signal(SIGTTOU, NULL);
	}
	return (1);
}

int			control_gprocess(int gpid)
{
	int fd;

	if ((fd = open(g_ttyname, O_RDWR)) == -1)
		return (ft_perror("42sh: tty:"));
	res_ign_ttin_ttou(1, gpid);
	if (tcsetpgrp(fd, gpid) == -1)
	{
		close(fd);
		res_ign_ttin_ttou(2, gpid);
		ft_perror("42sh: tcsetpgrp");
		return (-1);
	}
	close(fd);
	res_ign_ttin_ttou(2, gpid);
	return (1);
}

int			parent_job(int pgid, int bg, t_parse *execution)
{
	int		status;
	int		st_first_exit_cmd;

	status = 0;
	st_first_exit_cmd = -1;
	while (!bg && waitpid(pgid * -1, &status, WUNTRACED) > 0)
		if (WIFSTOPPED(status))
			break ;
		else if (st_first_exit_cmd == -1)
			st_first_exit_cmd = status;
	if (!bg && control_gprocess(getpgrp()) == -1)
		return (-1);
	if (!bg)
	{
		if_signaled(st_first_exit_cmd) != 0 ? ft_putchar_fd('\n', 2) : 0;
		if_suspend(status, pgid, execution, g_jobs);
	}
	else
		if_background(pgid, execution, g_jobs);
	return (st_first_exit_cmd);
}
