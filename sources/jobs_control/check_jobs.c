/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 23:47:22 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/15 23:48:06 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			jobs_next_node(t_parse **node, t_parse *next_node)
{
	(*node)->if_fail = NULL;
	(*node)->if_seccess = NULL;
	exit_parsing(node, NULL, 1);
	(*node) = next_node;
}

int				jobs_next_operator(t_parse **exec, int status)
{
	if (status != 0 && !(*exec)->if_fail && (*exec)->if_seccess)
	{
		jobs_next_node(exec, (*exec)->if_seccess);
		return (jobs_next_operator(exec, status));
	}
	if (status == 0 && !(*exec)->if_seccess && (*exec)->if_fail)
	{
		jobs_next_node(exec, (*exec)->if_fail);
		return (jobs_next_operator(exec, status));
	}
	if (status == 0 && (*exec)->if_seccess)
		jobs_next_node(exec, (*exec)->if_seccess);
	else if (status != 0 && (*exec)->if_fail)
		jobs_next_node(exec, (*exec)->if_fail);
	else
		exit_parsing(exec, NULL, 1);
	if (!*exec)
		return (0);
	return (1);
}

void			if_jobsexited(int status, t_jobs *nod)
{
	inform_user(nod, status, JOBS_ID | JOBS_CUR
			| JOBS_STAT | JOBS_CMD | JOBS_PGID);
	ft_putchar('\n');
	jobs_next_operator(&nod->node_cmd, get_exit_status(status));
	if (!nod->node_cmd)
	{
		(nod->proc_id == (g_last_jobs_id - 1)) ? g_last_jobs_id-- : 0;
		delete_node(nod);
	}
	else
	{
		nod->node_cmd->bg = 1;
		nod->mode |= (IS_BACKGROUND);
		nod->pgid = exec_lstpipe(nod->node_cmd, 0);
		inform_user(nod, 0, JOBS_ID | JOBS_CUR | JOBS_PGID | JOBS_MODE
				| JOBS_ALLCMD | JOBS_BG);
		ft_putchar('\n');
	}
}
