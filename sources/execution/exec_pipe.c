/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 21:40:41 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 17:15:43 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	exec_if_builtin(t_parse *node_c,
int *builtin_exit, t_exec_objet obj)
{
	char	**av;
	int		i;

	i = 0;
	av = clear_quots(ft_cmdsplit(node_c->cmd, ' '));
	if (is_abuiltin(node_c, av, builtin_exit))
		i = 1;
	ft_freetable(&av);
	if (i == 1)
	{
		close(obj.pip[0]);
		close(obj.pip[1]);
	}
	return (i);
}

static int	pipe_managment(int pip[2], int *oldppr,
int aft, int bfr)
{
	if (aft && pipe(pip) == -1)
		return (ft_perror("42sh: pipe"));
	if (bfr)
	{
		close(pip[1]);
		if (*oldppr)
			close(*oldppr);
		*oldppr = pip[0];
	}
	return (1);
}

static int	creation_child(t_parse *lst, t_exec_objet obj)
{
	if (!(lst->pid = fork()))
	{
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		child_job(lst, obj.pip, obj.old_ppr, obj.proc_nbr);
	}
	else if (lst->pid == -1)
		return (-1);
	return (1);
}

static void	int_objet(t_exec_objet *obj, int bg)
{
	obj->pgrp = 0;
	obj->proc_nbr = 0;
	obj->bg = bg;
	obj->old_ppr = 0;
}

int			exec_lstpipe(t_parse *lst, int mode)
{
	t_exec_objet obj;

	int_objet(&obj, lst->bg);
	while (lst)
	{
		if (pipe_managment(obj.pip, &obj.old_ppr, 1, 0) == -1
		|| set_cmd(lst) == -1)
			return (-1);
		if (!mode && obj.proc_nbr == 0 && !lst->pipe
		&& !obj.bg && exec_if_builtin(lst, &obj.builtin_exit, obj))
			return (ft_endoftmp(1));
		if (creation_child(lst, obj) == -1)
			return (ft_endoftmp(ft_perror("42sh: fork")));
		if (pipe_managment(obj.pip, &obj.old_ppr, 0, 1) == -1)
			return (-1);
		obj.pgrp = (obj.proc_nbr == 0) ? lst->pid : obj.pgrp;
		if ((++obj.proc_nbr) && !mode && setpgid(lst->pid, obj.pgrp) == -1)
			return (ft_endoftmp(ft_perror("42sh: setpgid")));
		(obj.pgrp == lst->pid && !mode && !obj.bg && (obj.bg = 1))
		? control_gprocess(obj.pgrp) : 0;
		lst = lst->pipe;
		ft_endoftmp(0);
	}
	close(obj.old_ppr);
	return (obj.pgrp);
}
