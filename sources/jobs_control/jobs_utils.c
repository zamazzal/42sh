/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 00:12:55 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 23:47:39 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		autre_signals(int status)
{
	if (WTERMSIG(status) == SIGQUIT)
		ft_putstr_fd("Quit Progam ", 2);
	else if (WTERMSIG(status) == SIGILL)
		ft_putstr_fd("Illegal Instruction ", 2);
	else if (WTERMSIG(status) == SIGTRAP)
		ft_putstr_fd("Trace Trap ", 2);
	else if (WTERMSIG(status) == SIGTERM)
		ft_putstr_fd("Process Terminated ", 2);
	else if (WTERMSIG(status) == SIGPIPE)
		ft_putstr_fd("Broken pipe: 13 ", 2);
	else
		return (1);
	return (0);
}

int				if_signaled(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGSEGV)
			ft_putstr_fd("Segmentation Violation ", 2);
		else if (WTERMSIG(status) == SIGABRT)
			ft_putstr_fd("Abort Program ", 2);
		else if (WTERMSIG(status) == SIGBUS)
			ft_putstr_fd("Bus Error ", 2);
		else if (WTERMSIG(status) == SIGKILL)
			ft_putstr_fd("Program Killed ", 2);
		else if (autre_signals(status))
		{
			ft_putstr_fd("Killed By Signal (", 2);
			ft_putnbr_fd((int)WTERMSIG(status), 2);
			ft_putstr_fd(") ", 2);
		}
	}
	else
		return (0);
	return (1);
}

void			delete_node(t_jobs *node)
{
	t_jobs	*ptr;
	t_jobs	*previous;

	previous = NULL;
	if (!node || !(ptr = get_jobsid(g_jobs, &previous, node->proc_id)))
		return ;
	if (ptr && ptr->pgid == node->pgid)
	{
		if (previous)
			previous->next = node->next;
		else
			g_jobs = g_jobs->next;
		if (ptr->proc_id == g_current_jobs->proc_id)
		{
			if (previous)
				g_current_jobs = previous;
			else
				g_current_jobs = g_jobs;
			if (g_current_jobs)
				g_current_jobs->mode |= (IS_SELECTED);
		}
		exit_parsing(&node->node_cmd, NULL, 1);
		free(node);
	}
}

static void		ft_printline(char *cmd)
{
	if (g_readline && g_readline->line)
	{
		prompt();
		ft_putstr(cmd);
		ft_do_termcap("cr");
		ft_cursor_lastpos();
	}
}

void			check_lstjobs(void)
{
	t_jobs	*jobs;
	int		status;

	if (!(jobs = g_jobs))
		return ;
	while (jobs)
	{
		if (waitpid(jobs->pgid, &status, WNOHANG | WUNTRACED | WCONTINUED) != 0)
		{
			(g_readline && g_readline->line) ? ft_remove_line() : 0;
			if_suspend(status, jobs->pgid, jobs->node_cmd, jobs);
			if (WIFCONTINUED(status))
			{
				jobs->mode |= (IS_BACKGROUND);
				jobs->mode &= ~(IS_SUSPEND);
				inform_user(jobs, status, JOBS_ID | JOBS_CUR
				| JOBS_MODE | JOBS_STAT | JOBS_ALLCMD);
				ft_putchar('\n');
			}
			if (WIFEXITED(status) || WIFSIGNALED(status))
				if_jobsexited(status, jobs);
			ft_printline(g_readline->line);
		}
		jobs = jobs->next;
	}
}
