/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 10:27:17 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/21 12:20:12 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	ft_setterm(void)
{
	char	*termtype;
	char	term_buffer[2048];
	int		success;

	termtype = getenv("TERM");
	if (termtype == 0)
	{
		ft_putstr("Specify a terminal type with `setenv TERM <yourtype>'.\n");
		exit(0);
	}
	success = tgetent(term_buffer, termtype);
	if (success < 0)
	{
		ft_putstr("Could not access the termcap data base.\n");
		exit(0);
	}
	if (success == 0)
	{
		ft_putstr("Terminal type `%s' is not defined.\n");
		exit(0);
	}
	ft_cannonical_mod();
}

void	ft_cannonical_mod(void)
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_lflag |= (ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
}

void	ft_syncwin_size(void)
{
	struct winsize ws;

	ioctl(0, TIOCGWINSZ, &ws);
	g_readline->winsize = ws.ws_col;
}

void	ft_setting(void)
{
	g_readline->line = ft_mema(LINE_MAX);
	g_readline->linex = 0;
	g_readline->liney = 0;
	g_readline->linelen = 0;
	g_readline->totaly = 0;
	g_readline->curlinelen = 0;
	g_readline->tmplinex = 0;
	g_readline->index = 0;
	g_readline->is_tab = 0;
	g_readline->tab_calc = -4;
	g_readline->tab_while = 0;
	g_readline->lst_ps = 0;
}
