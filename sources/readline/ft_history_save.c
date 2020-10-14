/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_save.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:53:20 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/15 13:22:15 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_load_history(void)
{
	int		fd;
	char	*line;
	char	*tmp;
	char	buf[10];

	if ((fd = open(g_history_saved, O_RDONLY)) == -1)
		return ;
	line = ft_strnew(1);
	while (read(fd, &buf, 1))
	{
		if (buf[0] == 3)
		{
			ft_add_history(&line);
			ft_strdel(&line);
			line = ft_strnew(1);
		}
		else
		{
			tmp = ft_jandf(line, buf, 1, 0);
			line = tmp;
		}
	}
	ft_strdel(&line);
	close(fd);
}

void	ft_savein_file(char *line)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(g_history_saved, O_RDWR | O_APPEND
	| O_CREAT, S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH);
	ft_putstr_fd(line, fd);
	ft_putchar_fd(3, fd);
	close(fd);
}
