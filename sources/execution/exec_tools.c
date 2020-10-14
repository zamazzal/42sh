/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 23:55:12 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/16 04:52:57 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int	ft_getfreefd(int fd)
{
	int new;
	int trash[3];
	int i;

	i = 0;
	while ((new = dup(fd)) < 3)
		trash[i++] = new;
	close(fd);
	return (new);
}

int	restore_filds(void)
{
	int	fd;

	if ((fd = open(g_ttyname, O_RDWR)) == -1)
		return (1);
	fd = ft_getfreefd(fd);
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	close(fd);
	return (1);
}

int	get_exit_status(int status)
{
	int exit_status;

	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = 128 + WTERMSIG(status);
	else
		exit_status = 128 + WSTOPSIG(status);
	return (exit_status);
}

int	ft_init(t_parse *lst, char *fc)
{
	t_parse *parsin_fc;

	if ((parsin_fc = parse_lst(&fc)))
		exec_lstparse(parsin_fc, 0);
	exit_parsing(&parsin_fc, NULL, 1);
	if (ft_strstr(fc, "vim") || ft_strstr(fc, "nano") || ft_strstr(fc, "emacs"))
		g_exec_fc = 1;
	ft_strdel(&lst->cmd);
	lst->cmd = fc;
	return (1);
}
