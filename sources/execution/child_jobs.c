/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 01:24:02 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 16:56:29 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		**clear_quots(char **argv)
{
	int		i;
	char	*tmp;

	if (!argv)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		tmp = ms_expand_tilde(argv[i]);
		ft_strdel(&argv[i]);
		argv[i] = ft_strndup_shell(tmp, ft_strlen(tmp));
		ft_strdel(&tmp);
		i++;
	}
	return (argv);
}

static int	relation_proc(int proc_nbr, int next_proc, int oldppr, int pip[2])
{
	close(pip[0]);
	if (proc_nbr > 0)
	{
		dup2(oldppr, 0);
		close(oldppr);
	}
	if (next_proc)
		dup2(pip[1], 1);
	close(pip[1]);
	return (1);
}

static int	if_child_built(t_parse *lst, char ***arg, char **replace_fc)
{
	int	builtin_exit;

	*replace_fc = NULL;
	if (!*arg)
		return (-1);
	if (ft_strequ((*arg)[0], "fc"))
	{
		builtin_exit = ft_fc_built(*arg, replace_fc);
		if (*replace_fc)
		{
			g_exec_fc = 1;
			ft_freetable(arg);
			*arg = clear_quots(ft_cmdsplit(*replace_fc, ' '));
			lst->path = ft_getpath(*replace_fc);
			ft_strdel(replace_fc);
			return (1);
		}
		else
			exit(builtin_exit);
	}
	if (is_abuiltin(lst, *arg, &builtin_exit))
		exit(builtin_exit);
	return (1);
}

void		child_job(t_parse *lst, int pip[2], int oldpr, int proc_nbr)
{
	char		**argv;
	struct stat	st;
	char		*replace_fc;

	relation_proc(proc_nbr, (lst->pipe) ? 1 : 0, oldpr, pip);
	if (exec_redirection(lst->lst_reder_aggr, &lst->cmd) == -1)
		exit(EXIT_FAILURE);
	argv = clear_quots(ft_cmdsplit(lst->cmd, ' '));
	if (if_child_built(lst, &argv, &replace_fc) == -1)
		exit(EXIT_FAILURE);
	if (!lst->path)
		exit(ft_notfound(lst->cmd));
	execve(lst->path, argv, g_environ);
	if (!(access(lst->path, F_OK)))
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(lst->path, 2);
		if (stat(lst->path, &st) != -1 && S_ISDIR(st.st_mode))
			ft_putendl_fd(": is a directory", 2);
		else
			ft_perror("");
		exit(126);
	}
	exit(127);
}
