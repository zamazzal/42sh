/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 10:21:08 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/12 16:54:40 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_defult_term(void)
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag |= (ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
}

void	prompt(void)
{
	if (g_line_type == L_DQ)
		ft_putstr("dquote> \n");
	else if (g_line_type == L_HDC)
		ft_putstr("herdoc> \n");
	else if (g_line_type == L_SQ)
		ft_putstr("quote> \n");
	else if (g_line_type == L_PIPE)
		ft_putstr("pipe> \n");
	else if (g_line_type == L_CMDAND)
		ft_putstr("cmdand> \n");
	else if (g_line_type == L_CMDOR)
		ft_putstr("cmdor> \n");
	else if (g_line_type == L_B)
		ft_putstr("> \n");
	else
		ft_putstr("42sh$> \n");
}

char	*ft_readline(char *prompt)
{
	char	key[BUFF_SIZE];
	int		ret;
	char	*line;

	ft_putstr(prompt);
	ft_setting();
	g_insert = g_readline;
	ft_signal_handler(g_insert);
	g_readline->history_search = 0;
	while (1)
	{
		ft_bzero(key, BUFF_SIZE);
		ft_syncwin_size();
		if ((ret = read(0, &key, BUFF_SIZE)) == -1 ||
				(key[0] == ENTER_KEY && key[1] == 0) ||
				!ft_key_detect(key))
		{
			ft_moveend();
			ft_history_expansions();
			line = ft_strdup(g_readline->line);
			ft_strdel(&g_readline->line);
			ft_defult_term();
			return (line);
		}
	}
}
