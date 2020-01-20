/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 20:23:49 by hessabra          #+#    #+#             */
/*   Updated: 2019/03/10 05:34:12 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		ft_conversion(const char *format, int *i)
{
	if (format[*i] != 'c' && format[*i] != 's' && format[*i] != 'p'
			&& format[*i] != 'd' && format[*i] != 'i' && format[*i] != 'o'
			&& format[*i] != 'u' && format[*i] != 'x' && format[*i] != 'X'
			&& format[*i] != 'f')
		return ((char)NULL);
	return (format[*i]);
}
