/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_incremental_search.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:42:34 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/15 23:43:15 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_hist_search(char *line)
{
	int	i;

	i = g_readline->indexfor_history - 1;
	while (i >= 0)
	{
		if (ft_strstr(g_readline->history[i], line))
			return (i);
		i--;
	}
	return (-1);
}

void	prompt_hist(char *line, t_read *g_readline, int index)
{
	g_readline->lst_ps ? ft_do_termcap("rc") : g_readline->lst_ps;
	ft_do_termcap("cr");
	ft_do_termcap("cd");
	ft_putstr("reverse-i-search)`");
	if (line)
		ft_putstr(line);
	ft_do_termcap("sc");
	g_readline->lst_ps = 5;
	ft_putstr("':");
	if (index >= 0)
		ft_putstr(g_readline->history[index]);
}

void	ft_return_search(int index)
{
	if (index >= 0)
	{
		ioctl(0, TIOCSTI, "\12");
		ft_addtoline(g_readline->history[index]);
	}
	else
		ioctl(0, TIOCSTI, "\12");
}

char	*ft_check_input(char *line, char *key, int *index)
{
	int			tmpindex;
	char		*tmp;

	tmpindex = *index;
	tmp = ft_strjoin(line, key);
	*index = ft_hist_search(tmp);
	ft_strdel(&tmp);
	if (*index >= 0)
		line = ft_strjoin_lite(line, key);
	else
	{
		*index = tmpindex;
		return (line);
	}
	return (line);
}

void	ft_search_hist(void)
{
	char	*line;
	int		index;
	char	key[6];

	if (!g_readline->history)
		return ;
	line = ft_strnew(2);
	index = -1;
	ft_bzero(key, 6);
	prompt_hist(line, g_readline, index);
	while (1)
	{
		if (read(0, &key, 6) != -1 && ft_isprint(key[0]))
		{
			line = ft_check_input(line, key, &index);
			prompt_hist(line, g_readline, index);
		}
		if (MOVE_RIGHT || MOVE_LEFT || key[0] == ENTER_KEY)
		{
			ft_return_search(index);
			ft_strdel(&line);
			return ;
		}
		ft_bzero(key, 6);
	}
}
