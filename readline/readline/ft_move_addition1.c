/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_addition1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:38:52 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/21 12:04:25 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_remove_line1(void)
{
	int i;

	i = g_readline->liney;
	if (i)
		while (i--)
			ft_do_termcap(CURSOR_UP);
	ft_do_termcap(CURSOR_CORNER);
}

void	ft_movestart(void)
{
	ft_remove_line1();
	g_readline->linex = 0;
	g_readline->liney = 0;
	g_readline->index = 0;
}

void	ft_moveend(void)
{
	while (g_readline->index < g_readline->linelen)
		ft_movecursor_right();
}
