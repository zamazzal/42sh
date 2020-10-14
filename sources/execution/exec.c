/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:18:23 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/16 04:52:59 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				is_abuiltin(t_parse *lst, char **argv, int *builtin_exit)
{
	int		rzlt;
	char	*fc;

	if (!(fc = NULL) && (!argv || !if_builtin(argv[0])))
		return (0);
	if (getpid() == g_shell_pid &&
exec_redirection(lst->lst_reder_aggr, &lst->cmd) == -1)
		return (restore_filds());
	if (!ft_strcmp(argv[0], "fc"))
		*builtin_exit = ft_fc_built(argv, &fc);
	else if ((rzlt = ft_builtins(argv)) != -1)
		*builtin_exit = rzlt;
	else if (!ft_strcmp(argv[0], "jobs"))
		*builtin_exit = jobs_builtin(argv);
	else if (!ft_strcmp(argv[0], "fg"))
		*builtin_exit = fg_builtin(argv);
	else if (!ft_strcmp(argv[0], "bg"))
		*builtin_exit = bg_builtin(argv);
	else if (!ft_strcmp(argv[0], "exit"))
		*builtin_exit = ft_exit(argv);
	if (getpid() == g_shell_pid && restore_filds())
		ft_setstatus_var(*builtin_exit);
	if (fc && (getpid() == g_shell_pid))
		return (ft_init(lst, fc));
	return (1);
}

int				next_operator(t_parse **lst, t_parse **execution, int status)
{
	if (status != 0 && !(*execution)->if_fail &&
(*execution)->if_seccess && ((*execution) = (*execution)->if_seccess))
		return (next_operator(lst, execution, status));
	if (status == 0 && !(*execution)->if_seccess &&
(*execution)->if_fail && ((*execution) = (*execution)->if_fail))
		return (next_operator(lst, execution, status));
	if (status == 0 && (*execution)->if_seccess)
		(*execution) = (*execution)->if_seccess;
	else if (status != 0 && (*execution)->if_fail)
		(*execution) = (*execution)->if_fail;
	else
	{
		(*lst) = (*lst)->next;
		(*execution) = (*lst);
	}
	return (1);
}

static void		exec_inside_random_save(void)
{
	t_parse	*lst;
	char	*line;
	int		fd;

	if ((fd = open(g_random_save, O_RDONLY)) == -1)
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		ft_putendl(line);
		if ((lst = parse_lst(&line)))
			exec_lstparse(lst, 0);
		ft_saveinhistory(line);
		free(line);
		exit_parsing(&lst, NULL, 1);
	}
	close(fd);
}

void			exec_lstparse(t_parse *lst, int mode)
{
	t_parse	*execution;
	int		status;
	int		pgrp;

	execution = lst;
	g_exec_fc = 0;
	while (execution)
	{
		if (mode != 0)
			execution->bg = 0;
		if ((pgrp = exec_lstpipe(execution, mode)) == -1)
			return ;
		if ((pgrp > 1) && !mode)
		{
			status = parent_job(pgrp, execution->bg, execution);
			ft_setstatus_var(get_exit_status(status));
		}
		if (g_exec_fc == 1 && !(g_exec_fc = 0)
		&& !ft_atoi(ft_getintern("status")))
			exec_inside_random_save();
		next_operator(&lst, &execution, ft_atoi(ft_getintern("status")));
	}
}
