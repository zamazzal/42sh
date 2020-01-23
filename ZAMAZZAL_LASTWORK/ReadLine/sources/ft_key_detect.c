/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_detect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 10:57:01 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/21 15:18:52 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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

char	*check_char(char *key)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = ft_strnew(ft_strlen(key));
	i = 0;
	j = 0;
	while (key[i] != '\0')
	{
		if (key[i] != '\t' && key[i] != '\n' && !ft_isprint(key[i]))
			i++;
		else if (key[i - 1] == '[' && (key[i] == 'C' ||
		key[i] == 'D' || key[i] == 'A' || key[i] == 'D'))
			i++;
		else
			tmp[j++] = key[i];
		i++;
	}
	return (tmp);
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
	replace_tab();
	if (ft_isprint(key[0]) || key[0] == '\n' || key[0] == '\t')
	{
		if (key[0] == '\t')
			key[0] = calc_tab(g_readline->index);
		if (key[1] == '\t')
			exit(0);
		if (key[2] == '\t')
			exit(0);
		if (key[3] == '\t')
			exit(0);
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
