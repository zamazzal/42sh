/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_cut.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:51:06 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/21 14:47:36 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	allocc(void)
{
	if (g_readline->topast == NULL)
		g_readline->topast = ft_mema(LINE_MAX);
	else if (g_readline->topast)
	{
		ft_strdel(&g_readline->topast);
		g_readline->topast = ft_mema(LINE_MAX);
	}
}

void	ft_copy(char *key)
{
	allocc();
	if (COPY)
		g_readline->topast = ft_strncpy(g_readline->topast,
		g_readline->line, g_readline->index);
	else if (COPY2)
		g_readline->topast = ft_strncpy(g_readline->topast, g_readline->line +
		g_readline->index, g_readline->linelen - g_readline->index);
	else if (COPY3)
		g_readline->topast = ft_strcpy(g_readline->topast, g_readline->line);
}

void	ft_cut1(void)
{
	char *tmp;

	g_readline->topast = ft_strncpy(g_readline->topast,
	g_readline->line, g_readline->index);
	tmp = ft_strsub(g_readline->line,
	g_readline->index, ft_strlen(g_readline->line));
	ft_bzero(g_readline->line, LINE_MAX);
	g_readline->line = ft_strcpy(g_readline->line, tmp);
	g_readline->index = ft_strlen(g_readline->line);
	g_readline->linelen = ft_strlen(g_readline->line);
	ft_strdel(&tmp);
}

void	ft_cut11(void)
{
	ft_cut1();
	ft_remove_line();
	ft_putstr(g_readline->line);
	g_readline->totaly = ft_totaly_count();
	g_readline->liney = g_readline->totaly;
	g_readline->linex = ft_curlinelen(g_readline->liney);
}

void	ft_cut(char *key)
{
	allocc();
	if (CUT)
	{
		g_readline->topast = ft_strncpy(g_readline->topast, g_readline->line
		+ g_readline->index, g_readline->linelen - g_readline->index);
		ft_bzero(g_readline->line + g_readline->index,
		LINE_MAX - g_readline->index);
	}
	else if (CUT2)
	{
		g_readline->topast = ft_strncpy(g_readline->topast,
			g_readline->line, g_readline->linelen);
		ft_clear_screen();
		return ;
	}
	else if (CUT1)
	{
		ft_cut11();
		return ;
	}
	g_readline->linelen = ft_strlen(g_readline->line);
	ft_remove_line();
	ft_putstr(g_readline->line);
	g_readline->totaly = ft_totaly_count();
	ft_cursor_lastpos();
}
