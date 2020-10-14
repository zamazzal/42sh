/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 06:00:59 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/02 22:31:50 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf(char *format, ...)
{
	va_list	ap;
	size_t	i;
	ushort	flag;

	flag = 0;
	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (flag == 0 && (flag = 1))
			ft_putstr_to(&format[i], '%');
		if (format[i] == '%')
		{
			i += search_format(&format[i], ap);
			flag = 0;
			continue;
		}
		i++;
	}
	va_end(ap);
}
