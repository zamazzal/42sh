/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pourcent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:31:41 by hessabra          #+#    #+#             */
/*   Updated: 2019/10/08 05:29:58 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_racc(const char *format, t_need *a, int *s, int *i)
{
	*s = *i;
	while (format[*i] == '%')
		(*i)++;
	if (!(((*i) - *s) % 2))
	{
		a->lenth = ((*i) - *s) / 2;
		a->result = -1;
		a->flag = NULL;
		return (1);
	}
	return (0);
}

static void	ft_racc2(const char *format, int *i, t_need *a, int s)
{
	a->conv = ft_conversion(format, &(*i));
	if (a->conv == (char)NULL)
	{
		a->result = -2;
		return ;
	}
	a->result = s;
}

t_need		ft_pourcent(const char *format, int *i)
{
	int		s;
	int		c;
	int		e;
	int		*f;
	t_need	a;

	if (ft_racc(format, &a, &s, &(*i)))
		return (a);
	c = -1;
	f = (int *)ft_mema(sizeof(int) * 5);
	while ((++c) < 5)
		f[c] = 0;
	s = ((*i) - s) / 2;
	e = *i;
	a.flag = ft_flags(format, &(*i), e, f);
	c = *i;
	a.width = ft_width(format, &(*i), c);
	c = *i;
	a.precision = ft_precision(format, &(*i), c);
	a.lenth = ft_lenth(format, &(*i));
	ft_racc2(format, &(*i), &a, s);
	return (a);
}
