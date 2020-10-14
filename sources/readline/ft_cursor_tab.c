/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:12:29 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/21 12:15:19 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_movecursor_left1(char *buf)
{
	int i;

	if (g_readline->index > 0)
	{
		if (!g_readline->liney || (g_readline->linex && g_readline->liney))
		{
			ft_do_termcap(CURSOR_LEFT);
			g_readline->linex--;
		}
		else if (g_readline->liney > 0 && g_readline->linex == 0)
		{
			g_readline->liney--;
			if ((g_readline->liney == 0 &&
			g_readline->line[0] == '\n') || g_readline->a)
				i = ft_fornor();
			else if (buf[0] == 127)
				i = ft_deletemulti();
			else
				i = ft_formove();
			ft_do_termcap(CURSOR_UP);
			while (i--)
				ft_do_termcap(CURSOR_RIGHT);
		}
		g_readline->tab_while <= 0 ? g_readline->index-- : g_readline->index;
	}
}

void	ft_movecursor_tab(void)
{
	int	i;

	i = 0;
	while (i < g_readline->line[g_readline->index] * -1)
	{
		if (g_readline->index < g_readline->linelen)
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
		}
		i++;
	}
	g_readline->index++;
}

void	ft_moveleft_tab(char *buf)
{
	int	j;
	int k;

	j = 0;
	k = 0;
	if (g_readline->is_tab > 0)
		k = g_readline->is_tab;
	else
		k = g_readline->line[g_readline->index - 1] * -1;
	g_readline->tab_while = 1;
	while (j < k)
	{
		ft_movecursor_left1(buf);
		j++;
	}
	g_readline->index--;
	g_readline->tab_while = 0;
}
