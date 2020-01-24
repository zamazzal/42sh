/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:24:54 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/21 14:31:54 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_deletemulti(void)
{
	int	i;

	if (g_readline->tmplinex >= g_readline->winsize)
	{
		i = g_readline->winsize;
		g_readline->linex = g_readline->winsize - 1;
	}
	else
	{
		i = g_readline->tmplinex;
		g_readline->linex = g_readline->tmplinex;
	}
	return (i);
}

int		ft_formove(void)
{
	int	i;

	i = ft_curlinelen(g_readline->liney);
	if (i >= g_readline->winsize)
		g_readline->linex = g_readline->winsize - 1;
	else
		g_readline->linex = i;
	return (i);
}

int		ft_fornor(void)
{
	int	i;

	g_readline->linex = 0;
	i = 0;
	return (i);
}

void	ft_movecursor_left(char *buf)
{
	if ((buf[0] != 127 &&
	g_readline->line[g_readline->index - 1] < 0) || g_readline->is_tab)
	{
		ft_moveleft_tab(buf);
		g_readline->is_tab = 0;
	}
	else
		ft_movecursor_left1(buf);
}

void	ft_movecursor_right(void)
{
	if (g_readline->line[g_readline->index] < 0)
		ft_movecursor_tab();
	else if (g_readline->index < g_readline->linelen)
	{
		if (g_readline->linex < (g_readline->winsize - 1) &&
				g_readline->line[g_readline->index] != '\n')
		{
			ft_do_termcap(CURSOR_RIGHT);
			g_readline->linex++;
		}
		else
		{
			ft_do_termcap("cr");
			ft_do_termcap("sf");
			g_readline->linex = 0;
			g_readline->liney++;
		}
		g_readline->index++;
	}
}
