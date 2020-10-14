/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_useless.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:42:08 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/12 19:45:17 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	useless(int *x, int *y)
{
	*x = 0;
	(*y)++;
}

void	useless2(int index, int *x)
{
	if (g_readline->line[index] < 0)
		*x += g_readline->line[index] * -1;
	else
		(*x)++;
}

void	useless3(int *x, int *y)
{
	*x = 0;
	(*y)++;
}
