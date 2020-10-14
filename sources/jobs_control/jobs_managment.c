/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 05:41:27 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 23:51:33 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static t_parse	*move_execution_node(t_parse *execution, t_parse **dest)
{
	if (!(*dest = (t_parse*)ft_memalloc(sizeof(t_parse))))
		return (NULL);
	(*dest)->cmd = execution->cmd;
	execution->cmd = NULL;
	(*dest)->if_fail = execution->if_fail;
	execution->if_fail = NULL;
	(*dest)->if_seccess = execution->if_seccess;
	execution->if_seccess = NULL;
	(*dest)->pipe = execution->pipe;
	execution->pipe = NULL;
	(*dest)->pid = execution->pid;
	(*dest)->lst_reder_aggr = execution->lst_reder_aggr;
	execution->lst_reder_aggr = NULL;
	return (*dest);
}

int				set_jobs(int pgid, t_jobs **ptr, t_parse *exec)
{
	if (!(*ptr = (t_jobs*)ft_memalloc(sizeof(t_jobs))))
		return (ft_perror("42sh: malloc"));
	if (!((*ptr)->node_cmd = (t_parse*)ft_memalloc(sizeof(t_parse))))
		return (ft_perror("42sh: malloc"));
	(*ptr)->node_cmd->cmd = ft_strdup(exec->cmd);
	(*ptr)->node_cmd->pipe = exec->pipe;
	exec->pipe = NULL;
	(*ptr)->node_cmd->lst_reder_aggr = exec->lst_reder_aggr;
	exec->lst_reder_aggr = NULL;
	(*ptr)->node_cmd->pid = exec->pid;
	(*ptr)->pgid = pgid;
	(*ptr)->proc_id = g_last_jobs_id;
	g_last_jobs_id++;
	return (1);
}

int				if_suspend(int status, int pgid,
t_parse *execution, t_jobs *ptr)
{
	if (WIFSTOPPED(status))
	{
		if (ptr && ptr->next && ptr->pgid != pgid)
			return (if_suspend(status, pgid, execution, ptr->next));
		if (((ptr && ptr->pgid != pgid) || !ptr) &&
set_jobs(pgid, (ptr != NULL) ? &ptr->next : &g_jobs, execution) == -1)
			return (-1);
		if (!ptr || (ptr->pgid != pgid))
			ptr = (ptr == NULL) ? g_jobs : ptr->next;
		if (g_current_jobs)
			g_current_jobs->mode &= ~(IS_SELECTED);
		g_current_jobs = ptr;
		ptr->mode = (IS_SELECTED | IS_SUSPEND);
		inform_user(ptr, status,
JOBS_ID | JOBS_CUR | JOBS_MODE | JOBS_STAT | JOBS_ALLCMD);
		ft_putchar('\n');
		return (1);
	}
	return (0);
}

int				if_background(int pgid, t_parse *execution, t_jobs *ptr)
{
	if (ptr && ptr->next)
		return (if_background(pgid, execution, ptr->next));
	if (ptr && !(ptr->next = (t_jobs*)ft_memalloc(sizeof(t_jobs))))
		return (ft_perror("42sh: malloc"));
	else if (!ptr && !(g_jobs = (t_jobs*)ft_memalloc(sizeof(t_jobs))))
		return (ft_perror("42sh: malloc"));
	ptr = (ptr == NULL) ? g_jobs : ptr->next;
	ptr->proc_id = g_last_jobs_id;
	g_last_jobs_id++;
	ptr->mode = IS_BACKGROUND;
	if (g_current_jobs && (g_current_jobs->mode & IS_BACKGROUND))
		g_current_jobs->mode &= ~(IS_SELECTED);
	if ((!g_current_jobs || (g_current_jobs->mode & IS_BACKGROUND))
	&& (g_current_jobs = ptr))
		ptr->mode |= IS_SELECTED;
	ptr->pgid = pgid;
	move_execution_node(execution, &ptr->node_cmd);
	inform_user(ptr, 0, JOBS_ID | JOBS_CUR | JOBS_PGID | JOBS_MODE
	| JOBS_ALLCMD | JOBS_BG);
	ft_putchar('\n');
	return (1);
}
