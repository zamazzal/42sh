/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_detect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 10:57:01 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/15 22:37:08 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_key_moves(char *key)
{
	if (MOVE_RIGHT)
		ft_movecursor_right();
	else if (MOVE_LEFT)
		ft_movecursor_left(key);
	else if (MOVE_UP)
		ft_movecursor_up();
	else if (MV_DWN)
		ft_movecursor_down();
	else if (MOVE_START)
		ft_movestart();
	else if (MOVE_END)
		ft_moveend();
	else if (MV_NEXT)
		ft_movecursor_next_word();
	else if (MV_BACK)
		ft_movecursor_back_word(key);
	else
		return (0);
	return (1);
}

int		ft_keyfer_moves(char *key)
{
	g_readline->curlinelen = ft_curlinelen(g_readline->liney);
	if (COPY || COPY3)
		ft_copy(key);
	if (CUT || CUT1 || CUT2)
		ft_cut(key);
	else if (DELETE)
		ft_delete_char(key);
	else if (DELETE_LINE)
		ft_search_hist();
	else if (key[0] == 4)
		ft_delete_onechar();
	else if (PAST && g_readline->topast)
	{
		ft_addtoline(g_readline->topast);
		g_readline->curlinelen = ft_curlinelen(g_readline->liney);
	}
	else if (HISTORY_MOVE_NEXT)
		ft_history_forwad();
	else if (HISTORY_MOVE_BACK)
		ft_history_back();
	else
		return (0);
	return (1);
}

void	replace_tab(void)
{
	int index;

	index = g_readline->index;
	if (index == g_readline->linelen)
		return ;
	while (g_readline->line[index] > 0)
	{
		index++;
		if (g_readline->line[index] < 0)
			g_readline->line[index] = calc_tab(index - 1);
	}
}

int		ft_key_detect(char *key)
{
	if (ft_isprint(key[0]) || key[0] == '\n' || key[0] == '\t')
	{
		replace_tab();
		if (key[0] == '\t')
			key[0] = calc_tab(g_readline->index);
		ft_addtoline(key);
		g_readline->curlinelen = ft_curlinelen(g_readline->liney);
		return (1);
	}
	else if (ft_keyfer_moves(key))
		return (1);
	else if (ft_key_moves(key))
		return (1);
	return (-1);
}
