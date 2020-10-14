/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_substitution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 12:06:40 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 17:06:55 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char	*getfifoname(void)
{
	int		index;
	char	*path;
	char	*fifo_name;
	char	*number;

	index = 0;
	number = ft_itoa(index++);
	fifo_name = ft_strjoin_lite(ft_strdup("/.42sh_fifo_"), number);
	path = ft_strjoin(ft_getenv("HOME"), fifo_name);
	ft_strdel(&number);
	ft_strdel(&fifo_name);
	while (access(path, F_OK) == 0)
	{
		ft_strdel(&path);
		number = ft_itoa(index++);
		fifo_name = ft_strjoin_lite(ft_strdup("/.42sh_fifo_"), number);
		path = ft_strjoin(ft_getenv("HOME"), fifo_name);
		ft_strdel(&number);
		ft_strdel(&fifo_name);
	}
	return (path);
}

int			proc_substitution_r(char *cmd, int pip[2], char **cal_cmd)
{
	int		fd;
	char	*fifo_path;
	t_parse	*lst;

	ft_change_chr_to_nwchr(cmd, '(', ' ');
	ft_change_chr_to_nwchr(cmd, ')', ' ');
	fifo_path = getfifoname();
	if (mkfifo(fifo_path, S_IRWXU | S_IRWXG) == -1)
		ft_perror("42sh: mkfifo");
	argument_join(cal_cmd, fifo_path);
	if (!fork())
	{
		if ((fd = open(fifo_path, O_WRONLY)) == -1)
			exit(EXIT_FAILURE);
		close(pip[0]);
		close(pip[1]);
		dup2(fd, 1);
		close(fd);
		if ((lst = parse_lst(&cmd)))
			exec_lstparse(lst, 1);
		unlink(fifo_path);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

int			proc_substitution_w(char *cmd, char **cal_cmd)
{
	t_parse	*lst;
	char	*fifo_path;

	cmd = ft_strdup(cmd);
	ft_change_chr_to_nwchr(cmd, '(', ' ');
	ft_change_chr_to_nwchr(cmd, ')', ' ');
	fifo_path = getfifoname();
	if (mkfifo(fifo_path, S_IRWXU | S_IRWXG) == -1)
		ft_perror("42sh: mkfifo");
	argument_join(cal_cmd, fifo_path);
	if (!fork())
	{
		if ((lst = parse_lst(&cmd)))
			exec_lstparse(lst, 1);
		unlink(fifo_path);
		exit(EXIT_SUCCESS);
	}
	else
		wait(NULL);
	return (1);
}
