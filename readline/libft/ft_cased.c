/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cased.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 12:18:51 by hessabra          #+#    #+#             */
/*   Updated: 2019/10/08 05:29:58 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_cased.h"

static int	ft_racc(t_need *a, int *c, va_list ap, char **tmp)
{
	int		i;

	if (a->width == -1)
		a->width = va_arg(ap, int);
	if (a->precision == -1)
		a->precision = va_arg(ap, int);
	if (a->lenth == 1)
		*c = va_arg(ap, long int);
	else if (a->lenth == 2)
		*c = va_arg(ap, long long int);
	else if (a->lenth == 3)
		*c = va_arg(ap, int);
	else if (a->lenth == 1)
		*c = va_arg(ap, int);
	else
		*c = va_arg(ap, int);
	if (*c < 0)
		i = *c * (-1);
	else
		i = *c;
	*tmp = ft_itoa(i);
	return (i);
}

static char	ft_racc1(t_need a, t_need5 r, char **new, char *tmp)
{
	if (r.i > a.precision && (r.i > a.width))
	{
		*new = (char *)ft_mema(sizeof(char) * (r.i + 1));
		*new = ft_memset(*new, ' ', r.i);
		if (a.flag[3] == 4 || r.c < 0)
			(*new)[0] = sign(r.c);
		*new = ft_strrv(*new, tmp);
		return (0);
	}
	else if (a.precision > a.width && r.i < a.precision)
	{
		*new = ft_strnew(a.precision + r.mc);
		*new = ft_memset(*new, '0', a.precision + r.mc);
		ft_strrv(*new, tmp);
		if (a.flag[3] == 4 || r.c < 0)
			(*new)[0] = sign(r.c);
		else if (a.flag[0] == 16)
			(*new)[0] = ' ';
		return (0);
	}
	return (1);
}

static int	ft_racc2(t_need a, t_need5 r, char **new, char *tmp)
{
	*new = ft_strnew(a.width);
	*new = ft_memset(*new, ' ', a.width);
	if ((a.flag)[4] == 8)
	{
		if (a.precision > (r.i - r.mc))
			*new = ft_strcp(*new, tmp, r.mc + (a.precision - r.i + 1));
		else
			*new = ft_strcp(*new, tmp, r.mc);
		if (a.flag[3] == 4 || r.c < 0)
		{
			(*new)[0] = sign(r.c);
			(r.i)--;
		}
		r.c = r.mc;
		while (a.precision > 0 && r.mc < a.precision - r.i + r.c)
		{
			(*new)[r.mc] = '0';
			(r.mc)++;
		}
		return (0);
	}
	return (1);
}

static void	ft_racc3(t_need a, t_need5 r, char **new, char *tmp)
{
	if (a.precision < r.i && ((a.flag)[1] == 1) && ((a.flag)[4] != 8))
	{
		r.mc = -1;
		*new = ft_memset(*new, '0', a.width);
	}
	*new = ft_strrv(*new, tmp);
	if (a.flag[3] == 4 || r.c < 0)
	{
		if (r.mc == -1)
			*new[0] = sign(r.c);
		else if (a.precision > r.i)
			*new[a.width - a.precision - 1] = sign(r.c);
		else
			*new[a.width - r.i] = sign(r.c);
		(r.i)--;
	}
	r.c = a.width;
	while (a.precision > 0 && a.width - a.precision < r.c - r.i)
	{
		*new[a.width - a.precision] = '0';
		(a.width)++;
	}
}

char		*ft_cased(t_need a, va_list ap)
{
	t_need5	r;
	char	*new;
	char	*tmp;

	r.i = ft_racc(&a, &(r.c), ap, &tmp);
	r.mc = 0;
	if ((a.flag[3] == 4) || a.flag[0] == 16 || r.c < 0)
		r.mc = 1;
	r.i = ft_strlen(tmp) + r.mc;
	if (ft_racc1(a, r, &new, tmp))
	{
		if (ft_racc2(a, r, &new, tmp) == 1)
			ft_racc3(a, r, &new, tmp);
	}
	free(tmp);
	return (new);
}
