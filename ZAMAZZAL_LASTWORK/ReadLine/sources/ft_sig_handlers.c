/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 10:57:01 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/17 20:36:21 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	ft_signal_handler(t_read *g_readline)
{
	g_readline = g_insert;
	g_readline->index = g_readline->index;
	ft_cannonical_mod();
	signal(SIGINT, sigint_handler);
	signal(SIGWINCH, sigwinch_handler);
}

void	sigwinch_handler(int sig)
{
	char	*tmp;
	char	*key;

	key = 0;
	if (g_readline->line)
	{
		tmp = ft_strdup(g_readline->line);
		ft_do_termcap("ho");
		ft_clear_screen(g_readline);
		prompt();
		ft_syncwin_size(g_readline);
		ft_addtoline(tmp);
		ft_strdel(&tmp);
		(void)sig;
	}
}

void	sigint_handler(int sig)
{
	if (g_pid_cmd != 0 && g_is_pipe)
		ft_putchar('\n');
	else if (g_herdoc_sig == 1 && g_is_pipe)
	{
		g_herdoc_sig = 0;
		ioctl(0, TIOCSTI, "\12");
	}
	else
	{
		ft_remove_line(g_readline);
		ft_do_termcap(DELETE_AFTER_CURSOR);
		g_readline->linex = 0;
		g_readline->liney = 0;
		g_readline->linelen = 0;
		g_readline->totaly = 0;
		g_readline->curlinelen = 0;
		g_readline->tmplinex = 0;
		g_readline->index = 0;
		(void)sig;
		if (g_readline->history)
			g_readline->indexfor_history = ft_tablen(g_readline->history);
	}
}
