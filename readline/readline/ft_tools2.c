/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:21:12 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/21 14:32:50 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_putspace(int num)
{
	num *= -1;
	while (num-- > 0)
		ft_putchar(' ');
}

void	ft_puttab(void)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (g_readline->line[i] != '\0')
	{
		if (g_readline->line[i] < 0)
			ft_putspace(g_readline->line[i]);
		else
			ft_putchar(g_readline->line[i]);
		i++;
	}
}

void	ft_count_tab(int *x, int tabu, int *y)
{
	int	j;
	int	tmp;
	int	res;

	j = *y;
	tmp = tabu;
	res = 0;
	while (tabu >= 0)
	{
		if (*x + tabu == g_readline->winsize)
		{
			(*y)++;
			*x = res;
			return ;
		}
		tabu--;
		res++;
	}
	*x += tmp;
}
