/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 12:51:44 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/09 20:52:36 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_cursor_lastpos(void)
{
	int	yline;
	int	i;

	yline = g_readline->totaly;
	if (!((g_readline->curlinelen + 1) % g_readline->winsize))
		g_readline->totaly++;
	while (yline--)
		ft_do_termcap(CURSOR_UP);
	ft_do_termcap(CURSOR_CORNER);
	i = 0;
	while (i++ < g_readline->liney)
		ft_do_termcap(CURSOR_DOWN);
	i = 0;
	while (i++ < g_readline->linex)
		ft_do_termcap(CURSOR_RIGHT);
}

void	ft_remove_line(void)
{
	int	i;

	i = g_readline->liney;
	if (i)
		while (i--)
			ft_do_termcap(CURSOR_UP);
	ft_do_termcap(CURSOR_CORNER);
	ft_do_termcap(DELETE_AFTER_CURSOR);
}

char	*ft_addinput(char *buf)
{
	char	*tmpline;

	tmpline = ft_strsub(g_readline->line, g_readline->index,
			g_readline->linelen - g_readline->index);
	ft_bzero(g_readline->line +
	g_readline->index, LINE_MAX - g_readline->index);
	g_readline->line = ft_strcat(g_readline->line, buf);
	g_readline->line = ft_strcat(g_readline->line, tmpline);
	ft_strdel(&tmpline);
	return (g_readline->line);
}

int		calc_tab(int index)
{
	int	i;
	int	tab_n;

	tab_n = -1;
	i = 0;
	while (g_readline->line[index] > 0 && index >= 0)
	{
		index--;
		tab_n++;
	}
	return ((tab_n % 8) - 8);
}

void	ft_addtoline(char *buf)
{
	int		i;

	i = ft_strlen(buf);
	ft_remove_line();
	g_readline->line = ft_addinput(buf);
	ft_puttab();
	g_readline->linelen += i;
	g_readline->totaly = ft_totaly_count();
	ft_cursor_lastpos();
	while (i--)
		ft_movecursor_right();
}
