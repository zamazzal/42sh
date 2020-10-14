/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:09:23 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/12 19:41:58 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_curlinelen(int liney)
{
	int x;
	int y;
	int index;

	x = 0;
	y = 0;
	index = 0;
	while (index < g_readline->linelen)
	{
		x++;
		if (g_readline->line[index] < 0)
			ft_count_tab(&x, (g_readline->line[index] * -1) - 1, &y);
		if (g_readline->line[index] == '\n' || x == g_readline->winsize)
			useless(&x, &y);
		if (y == liney)
		{
			while (++index < g_readline->linelen
			&& g_readline->line[index] != '\n')
				useless2(index, &x);
			return (g_readline->curlinelen = x);
		}
		index++;
	}
	return (g_readline->curlinelen = x);
}

int		countbigy(char *buf)
{
	int i;

	i = 0;
	while (*buf)
	{
		if (*buf == '\n')
			i++;
		buf++;
	}
	return (i);
}

int		ft_totaly_count(void)
{
	int	i;
	int	index;
	int	x;
	int	y;

	x = 0;
	i = 0;
	index = 0;
	y = 0;
	while (index < g_readline->linelen)
	{
		if (g_readline->line[index] == '\n')
		{
			x = -1;
			y++;
		}
		if (g_readline->line[index] < 0)
			ft_count_tab(&x, (g_readline->line[index] * -1) - 1, &y);
		else if (x == g_readline->winsize)
			useless3(&x, &y);
		x++;
		index++;
	}
	return (y);
}

int		h_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

void	ft_do_termcap(char *termcap)
{
	tputs(tgetstr(termcap, NULL), 1, &h_putchar);
}
