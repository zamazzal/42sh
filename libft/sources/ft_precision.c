/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:34:10 by hessabra          #+#    #+#             */
/*   Updated: 2019/03/10 05:34:47 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_precision(const char *format, int *i, int r)
{
	char	*c;
	int		x;

	if (format[*i] == '.')
		(*i)++;
	else
		return (-2);
	if (format[*i] == '*')
		return (-1);
	while (ft_isdigit(format[*i]))
		(*i)++;
	c = ft_strsub(format, r + 1, (size_t)(*i));
	x = ft_atoi(c);
	free(c);
	return (x);
}
