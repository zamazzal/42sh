/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 10:21:08 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/22 18:48:15 by helmanso         ###   ########.fr       */
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
	ft_putstr("\e[35;1mWhat can I do for you ;) >>\n\e[0m");
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
			ft_fc_built();
			line = ft_strdup(g_readline->line);
			ft_strdel(&g_readline->line);
			return (line);
		}
	}
}
/*
int		main(void)
{
	char	*line;

	//ft_setterm();
	//g_readline = (t_read *)malloc(sizeof(t_read));
	//ft_load_history();
	while (1)
	{
		line = ft_readline("\e[35;1mysh $>\n\e[0m\n");
		ft_savein_file(line);
		ft_add_history(&line);
		ft_strdel(&line);
	}
}
*/