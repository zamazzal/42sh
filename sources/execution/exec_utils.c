/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:34:51 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 17:15:42 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				ft_notfound(char *cmd)
{
	if (cmd)
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(cmd, 2);
	}
	ft_setstatus_var(127);
	return (127);
}

char			*get_path_cmd(char *cmd)
{
	char *cmd_path;

	cmd_path = ft_checkcmd(cmd);
	return (cmd_path);
}

static void		change_cmd(char **cmd, int red_type)
{
	ft_strdel(cmd);
	if (red_type & READ_FILE)
		*cmd = ft_strdup("more");
	else
		*cmd = ft_strdup("cat");
}

int				set_cmd(t_parse *ptr)
{
	int ret;

	if (!ptr->cmd)
		return (-1);
	if (!ptr->cmd[0])
		change_cmd(&ptr->cmd, (ptr->lst_reder_aggr != NULL)
		? ptr->lst_reder_aggr->red_type : 0);
	ptr->cmd = ms_expand_dollars(&ret, ptr->cmd);
	if (!ptr->cmd || !ptr->cmd[0])
	{
		ptr->cmd ? free(ptr->cmd) : 0;
		ptr->cmd = ft_strdup("true");
	}
	if (ret == -2 || ret == -1)
		return (-1);
	ft_settmpvar(&ptr->cmd);
	ptr->path = ft_getpath(ptr->cmd);
	return (1);
}

char			*ft_getpath(char *cmd)
{
	char *path;
	char **argv;

	if (!(argv = clear_quots(ft_cmdsplit(cmd, ' '))))
		return (NULL);
	path = ft_getcmd_from_htab(argv[0]);
	if (!path)
	{
		if (!if_builtin(argv[0]) && (path = get_path_cmd(argv[0])))
		{
			ft_add_inhashtable(argv[0], path);
			ft_htab_addhit(argv[0]);
		}
	}
	ft_freetable(&argv);
	return (path);
}
