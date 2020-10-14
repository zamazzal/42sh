/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_built_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:42:58 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/15 23:21:50 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		ft_hist_l(void)
{
	if (!g_readline->num2)
		g_readline->num2 = g_readline->indexfor_history - 1;
	while (g_readline->num1 <= g_readline->num2
			&& g_readline->history[g_readline->num1])
	{
		if (!g_readline->n)
			ft_putnbr(g_readline->num1);
		ft_putstr("   ");
		ft_putendl(g_readline->history[g_readline->num1]);
		g_readline->num1++;
	}
	if (g_readline->editor)
		ft_strdel(&g_readline->editor);
}

void		ft_hist_lr(void)
{
	if (!g_readline->num2)
	{
		if (!g_readline->n)
			ft_putnbr(g_readline->num1);
		ft_putstr("   ");
		ft_putendl(g_readline->history[g_readline->num1]);
		return ;
	}
	while (g_readline->num1 >= g_readline->num2
			&& g_readline->history[g_readline->num1])
	{
		if (!g_readline->n)
			ft_putnbr(g_readline->num1);
		ft_putstr("   ");
		ft_putendl(g_readline->history[g_readline->num1]);
		g_readline->num1--;
	}
	if (g_readline->editor)
		ft_strdel(&g_readline->editor);
}

void		ft_do_args(void)
{
	if (g_readline->l && !g_readline->r)
		ft_hist_l();
	else if (g_readline->l && g_readline->r)
		ft_hist_lr();
	else if (!g_readline->l && !g_readline->r)
		ft_hist_e();
	else if (!g_readline->l && g_readline->r)
		ft_hist_er();
}

static	int	ft_return_fc(char **arg, int ret)
{
	ft_freetable(&arg);
	return (ret);
}

int			ft_fc_built(char **arg, char **line)
{
	if (!g_readline->linelen || !g_readline->history)
		return (1);
	ft_initialize_fc();
	arg = ft_check_all(arg);
	if (!ft_arg_nbr(arg) || ft_strcmp(arg[0], "fc"))
		return (ft_return_fc(arg, 1));
	if (!ft_strcmp(arg[0], "fc") && !arg[1])
		g_readline->num1 = g_readline->indexfor_history - 1;
	else if (ft_check_s(arg))
	{
		*line = ft_strdup(g_readline->editor);
		ft_strdel(&g_readline->editor);
		return (ft_return_fc(arg, 0));
	}
	if (!ft_check_args(arg) || !ft_check_args1(arg))
		return (ft_return_fc(arg, 1));
	ft_check_flag();
	ft_do_args();
	if (g_readline->editor)
		*line = ft_strdup(g_readline->editor);
	else
		*line = NULL;
	ft_strdel(&g_readline->editor);
	return (ft_return_fc(arg, 0));
}
