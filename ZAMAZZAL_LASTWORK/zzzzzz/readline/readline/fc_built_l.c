/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_built_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 23:11:04 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/21 15:40:38 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_initialize_fc(void)
{
	g_readline->e = 0;
	g_readline->n = 0;
	g_readline->r = 0;
	g_readline->num1 = 0;
	g_readline->num2 = 0;
	g_readline->l = 0;
}

void	ft_hist_l(void)
{
	if (ft_check_flag() == -1)
		return ;
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
}

void	ft_hist_lr(void)
{
	if (ft_check_flag() == -1)
		return ;
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
}

void	ft_do_args(void)
{
	if (g_readline->l && !g_readline->r)
		ft_hist_l();
	else if (g_readline->l && g_readline->r)
		ft_hist_lr();
	if (!g_readline->l && !g_readline->r)
		ft_hist_e();
	else if (!g_readline->l && g_readline->r)
		ft_hist_er();
}

void	ft_fc_built(void)
{
	int		i;
	char	**arg;

	i = 0;
	if (!g_readline->linelen || !g_readline->history)
		return ;
	arg = ft_strsplit(g_readline->line, ' ');
	ft_initialize_fc();
	if (!ft_arg_nbr(arg) || ft_strcmp(arg[0], "fc"))
	{
		dfre(arg);
		return ;
	}
	if (!ft_strcmp(arg[0], "fc") && !arg[1])
		g_readline->num1 = g_readline->indexfor_history - 1;
	else if (!ft_check_args(arg))
		return ;
	ft_do_args();
	dfre(arg);
}
