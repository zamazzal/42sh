/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:07:57 by hessabra          #+#    #+#             */
/*   Updated: 2019/03/10 05:34:18 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_racc(const char *format, int *i, int **s)
{
	if (format[*i] == ' ')
	{
		while (format[*i] == ' ')
			(*i)++;
		(*s)[0] = 16;
		return (1);
	}
	if (format[*i] == '0')
	{
		while (format[*i] == '0')
			(*i)++;
		(*s)[1] = 1;
		return (1);
	}
	return (0);
}

int			*ft_flags(const char *format, int *i, int c, int *s)
{
	if (ft_racc(format, &(*i), &(s)))
		return (ft_flags(format, i, c, s));
	if (format[*i] == '#')
	{
		while (format[*i] == '#')
			(*i)++;
		(s)[2] = 2;
		return (ft_flags(format, i, c, s));
	}
	if (format[*i] == '+')
	{
		while (format[*i] == '+')
			(*i)++;
		(s)[3] = 4;
		return (ft_flags(format, i, c, s));
	}
	if (format[*i] == '-')
	{
		while (format[*i] == '-')
			(*i)++;
		(s)[4] = 8;
		return (ft_flags(format, i, c, s));
	}
	return (s);
}
