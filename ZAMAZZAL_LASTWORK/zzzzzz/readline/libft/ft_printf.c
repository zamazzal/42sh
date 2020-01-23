/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 15:09:28 by hessabra          #+#    #+#             */
/*   Updated: 2019/03/10 05:44:44 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*string(int lenth)
{
	int			i;
	char		*cha;

	i = 0;
	cha = ft_strnew(lenth + 1);
	cha = ft_memset(cha, '%', lenth);
	cha[lenth] = '\0';
	return (cha);
}

static void		ft_racc(char *s, t_need a, va_list ap)
{
	if (a.conv == 's')
	{
		s = ft_cases(a, ap);
		ft_putstr(s);
		free(s);
	}
	if (a.conv == 'd' || a.conv == 'i')
	{
		s = ft_cased(a, ap);
		ft_putstr(s);
		free(s);
	}
}

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	t_need		a;
	int			i;
	char		*s;

	va_start(ap, format);
	i = 0;
	while (format[i])
	{
		a = ft_pourcent(format, &i);
		if (a.result == -1)
		{
			s = string(a.lenth);
			ft_putstr(s);
			free(s);
		}
		if (a.result > -1)
			ft_racc(s, a, ap);
		else
			ft_putchar(format[i]);
		i++;
		free(a.flag);
		a.flag = NULL;
	}
	return (i);
}
