/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenth.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:52:05 by hessabra          #+#    #+#             */
/*   Updated: 2019/03/10 05:34:33 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_racc(const char *format, int *i)
{
	if (format[*i] == 'l' && format[(*i) + 1] != 'l')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int				ft_lenth(const char *format, int *i)
{
	if (ft_racc(format, &(*i)))
		return (1);
	if (format[*i] == 'l' && format[(*i) + 1] == 'l')
	{
		*i = (*i) + 2;
		return (2);
	}
	if (format[*i] == 'L')
	{
		(*i)++;
		return (3);
	}
	if (format[*i] == 'h' && format[(*i) + 1] == 'h')
	{
		*i = (*i) + 2;
		return (4);
	}
	if (format[*i] == 'h' && format[(*i) + 1] != 'h')
	{
		(*i)++;
		return (5);
	}
	return (0);
}
