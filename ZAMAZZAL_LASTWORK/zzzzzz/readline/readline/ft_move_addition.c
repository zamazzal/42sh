/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_addition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:31:58 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/21 12:22:15 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_movecursor_next_word(void)
{
	int i;

	i = g_readline->index;
	while (g_readline->line[i] && g_readline->line[i] == '\n')
	{
		ft_movecursor_right();
		i++;
	}
	while (g_readline->line[i] && (g_readline->line[i]
	!= ' ' && g_readline->line[i] != '\n'))
	{
		ft_movecursor_right();
		i++;
	}
	while (g_readline->line[i] && (g_readline->line[i] == ' '))
	{
		ft_movecursor_right();
		i++;
	}
}

void	ft_movecursor_back_word(char *key)
{
	int i;

	i = g_readline->index;
	if (g_readline->line[i] && (g_readline->line[i - 1] == ' '
	|| g_readline->line[i] == '\n'))
	{
		i--;
		ft_movecursor_left(key);
	}
	while ((i > 0) && ((g_readline->line[i] == ' '
	|| g_readline->line[i] == '\0')))
	{
		ft_movecursor_left(key);
		i--;
	}
	while ((i > 0) && (g_readline->line[i] != ' '
	&& g_readline->line[i] != '\n'))
	{
		ft_movecursor_left(key);
		i--;
	}
	if (i > 0 && g_readline->line[i] == ' ')
		ft_movecursor_right();
}

void	ft_movecursor_up(void)
{
	int i;
	int j;
	int tmpx;
	int tmpy;

	if (g_readline->liney == 0)
	{
		ft_movestart();
		return ;
	}
	tmpx = g_readline->linex;
	tmpy = g_readline->liney - 1;
	j = ft_curlinelen(g_readline->liney) + 1;
	i = ft_curlinelen(g_readline->liney - 1);
	ft_movestart();
	while (g_readline->liney < tmpy)
		ft_movecursor_right();
	if (j > i && tmpx > i)
		tmpx = i;
	while (tmpx--)
		ft_movecursor_right();
}

void	ft_movecursor_down(void)
{
	int i;
	int j;
	int tmpx;
	int tmpy;

	if (g_readline->liney == g_readline->totaly)
	{
		ft_moveend();
		return ;
	}
	tmpx = g_readline->linex;
	tmpy = g_readline->liney + 1;
	j = ft_curlinelen(g_readline->liney) + 1;
	i = ft_curlinelen(g_readline->liney + 1);
	ft_movecursor_right();
	while (g_readline->liney < tmpy)
		ft_movecursor_right();
	if (j > i && tmpx > i)
		tmpx = i;
	while (tmpx--)
		ft_movecursor_right();
}
