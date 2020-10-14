/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delect_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:27:58 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/09 20:50:14 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_remove_fromline(void)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strsub(g_readline->line, 0, g_readline->index - 1);
	tmp2 = ft_strsub(g_readline->line, g_readline->index,
			g_readline->linelen - ft_strlen(tmp));
	ft_bzero(g_readline->line, 4096);
	g_readline->line = ft_strcpy(g_readline->line, tmp);
	g_readline->line = ft_strcat(g_readline->line, tmp2);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
}

void	ft_delete_char(char *buf)
{
	if (g_readline->index > 0)
	{
		g_readline->line[g_readline->index - 1] < 0 ? g_readline->is_tab =
		g_readline->line[g_readline->index - 1] * -1 : g_readline->is_tab;
		if (g_readline->linex == 0 || g_readline->line[g_readline->index - 1])
			g_readline->tmplinex = ft_curlinelen(g_readline->liney - 1);
		if (g_readline->liney == 1 && g_readline->line[0] == '\n')
			g_readline->a = 1;
		else
			g_readline->a = 0;
		ft_remove_line();
		ft_remove_fromline();
		ft_puttab();
		g_readline->linelen--;
		g_readline->totaly = ft_totaly_count();
		ft_cursor_lastpos();
		ft_movecursor_left(buf);
	}
}

void	ft_remove_one(void)
{
	char *tmp;
	char *tmp1;

	tmp = ft_strsub(g_readline->line, 0, g_readline->index);
	tmp1 = ft_strsub(g_readline->line, g_readline->index + 1,
	g_readline->linelen - ft_strlen(tmp));
	ft_bzero(g_readline->line, LINE_MAX);
	g_readline->line = ft_strcpy(g_readline->line, tmp);
	g_readline->line = ft_strcat(g_readline->line, tmp1);
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
}

void	ft_delete_onechar(void)
{
	if (g_readline->linelen == 0 && g_ctrl_dsig)
	{
		ioctl(0, TIOCSTI, "\12");
		g_ctrl_dsig = 0;
	}
	else if (g_readline->linelen == 0 && g_ctrl_dsig == 0)
	{
		ft_defult_term();
		exit(0);
	}
	if (g_readline->index >= 0 && g_readline->index < g_readline->linelen)
	{
		ft_remove_line();
		ft_remove_one();
		ft_putstr(g_readline->line);
		g_readline->linelen--;
		g_readline->totaly = ft_totaly_count();
		ft_cursor_lastpos();
	}
}
