/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 00:44:08 by hessabra          #+#    #+#             */
/*   Updated: 2019/02/03 02:52:28 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

const char		*fonction(const char *nptr, int x)
{
	int		y;
	char	*z;
	int		i;

	i = 0;
	z = (char *)nptr + x;
	nptr = z;
	while (z[i])
	{
		y = (int)z[i];
		if (!(ft_isdigit(y)))
		{
			nptr = ft_searchnreplace(z, y, 0);
			break ;
		}
		i++;
	}
	if (nptr[0] == '-')
		return (nptr + 1);
	return (nptr);
}

static int		rac(const char *nptr, int sign)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (sign == 1 && ft_strcmp(nptr, "9223372036854775807") >= 0
			&& ft_strlen(nptr) >= 19)
		return (-1);
	else if (sign == -1 && ft_strcmp(nptr, "9223372036854775808") >= 0
			&& ft_strlen(nptr) >= 19)
		return (0);
	else
	{
		if (nptr[0] == '-' || nptr[0] == '+')
			i = 1;
		while (nptr[i])
		{
			ret = ret * 10 + (nptr[i] - 48);
			i++;
		}
		return (ret);
	}
}

int				ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	int		ret;
	int		x;
	int		y;

	i = 0;
	sign = 1;
	while ((nptr[i] > 7 && nptr[i] < 14) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	x = i;
	nptr = fonction(nptr, x);
	y = (int)nptr[0];
	if (ft_isdigit(y))
	{
		ret = rac(nptr, sign);
		return (sign * ret);
	}
	return (0);
}
