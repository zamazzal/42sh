/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_save.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:53:20 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/21 14:45:57 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	ft_load_history(void)
{
	int		fd;
	char	*line;
	char	*tmp;
	char	buf[10];

	if ((fd = open("history_saved.txt", O_RDONLY)) == -1)
	{
		ft_putendl("open : error");
		return ;
	}
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
			tmp = ft_strjoin(line, buf);
			free(line);
			line = tmp;
		}
	}
	ft_strdel(&line);
}

void	ft_savein_file(char *line)
{
	int	i;
	int	fd;

	i = 0;
	fd = open("history_saved.txt", O_RDWR | O_APPEND | O_CREAT);
	ft_putstr_fd(line, fd);
	ft_putchar_fd(3, fd);
}
