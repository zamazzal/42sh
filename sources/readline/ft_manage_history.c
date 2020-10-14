/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:00:01 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/09 20:52:50 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_setting1(void)
{
	g_readline->linex = 0;
	g_readline->liney = 0;
	g_readline->linelen = 0;
	g_readline->totaly = 0;
	g_readline->curlinelen = 0;
	g_readline->tmplinex = 0;
	g_readline->index = 0;
	ft_bzero(g_readline->line, LINE_MAX);
}

void	ft_clear_screen(void)
{
	ft_remove_line();
	ft_do_termcap(DELETE_AFTER_CURSOR);
	ft_setting1();
}

void	ft_add_history(char **line)
{
	char	*temp;
	int		i;

	i = 0;
	if (g_readline->history &&
	g_readline->indexfor_history == ft_tablen(g_readline->history)
	&& !ft_strcmp(*line, ""))
		return ;
	if (g_readline->history &&
	g_readline->indexfor_history < ft_tablen(g_readline->history)
	&& !ft_strcmp(*line, ""))
		g_readline->indexfor_history = ft_tablen(g_readline->history);
	else
	{
		temp = ft_strsub(*line, 0, ft_strlen(*line));
		g_readline->history = ft_addtotab(g_readline->history, temp);
		ft_strdel(&temp);
		g_readline->indexfor_history = ft_tablen(g_readline->history);
	}
}

void	ft_history_back(void)
{
	if (!g_readline->history)
		return ;
	else
	{
		if (g_readline->indexfor_history > 0)
		{
			ft_clear_screen();
			g_readline->indexfor_history--;
			ft_addtoline(g_readline->history[g_readline->indexfor_history]);
		}
	}
}

void	ft_history_forwad(void)
{
	if (!g_readline->history)
		return ;
	else
	{
		if (g_readline->indexfor_history == ft_tablen(g_readline->history) - 1)
		{
			ft_clear_screen();
			g_readline->indexfor_history++;
		}
		if (g_readline->indexfor_history < ft_tablen(g_readline->history))
		{
			ft_clear_screen();
			g_readline->indexfor_history++;
			ft_addtoline(g_readline->history[g_readline->indexfor_history]);
		}
	}
}
