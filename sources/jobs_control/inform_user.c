/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inform_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 23:51:18 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/15 23:51:54 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			inform_status(int stat)
{
	WIFEXITED(stat) ? ft_printf("Done(%d) ", WEXITSTATUS(stat)) : 0;
	WIFSIGNALED(stat) ? if_signaled(stat) : 0;
	if (WIFSTOPPED(stat))
	{
		(WSTOPSIG(stat) == SIGTSTP) ? ft_printf("(SIGTSTP) ") : 0;
		(WSTOPSIG(stat) == SIGTTIN) ? ft_printf("(SIGTTIN) ") : 0;
		(WSTOPSIG(stat) == SIGTTOU) ? ft_printf("(SIGTTOU) ") : 0;
		(WSTOPSIG(stat) == SIGSTOP) ? ft_printf("(SIGSTOP) ") : 0;
	}
}

void			inform_user(t_jobs *node, int stat, int info)
{
	if ((info & JOBS_ID))
		ft_printf("[%d] ", node->proc_id);
	if ((info & JOBS_CUR))
		ft_printf("%c ", (node->mode & IS_SELECTED) > 0 ? '+' : '-');
	if ((info & JOBS_PGID))
		ft_printf("%d ", node->pgid);
	if ((info & JOBS_MODE))
		ft_printf("%s %s %s ", (node->mode & IS_SUSPEND) > 0 ? "Stopped" : "\0",
			(node->mode & IS_BACKGROUND) ? "Running" : "\0",
			!(node->mode & (IS_SUSPEND | IS_BACKGROUND)) ? "continued" : "\0");
	if ((info & JOBS_STAT))
		inform_status(stat);
	if ((info & JOBS_CMD))
		print_command_p(node->node_cmd);
	if ((info & JOBS_ALLCMD))
		print_command(node->node_cmd);
	if ((info & JOBS_BG) && (node->mode & IS_BACKGROUND))
		ft_printf(" &");
}
