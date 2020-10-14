/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 10:57:01 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/07 12:46:06 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

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
	g_ctrl_csig = 0;
	ioctl(0, TIOCSTI, "\12");
	ft_remove_line(g_readline);
	ft_do_termcap(DELETE_AFTER_CURSOR);
	ft_putstr(g_readline->line);
	ft_strdel(&g_readline->line);
	ft_setting();
	(void)sig;
	if (g_readline->history)
		g_readline->indexfor_history = ft_tablen(g_readline->history);
}
