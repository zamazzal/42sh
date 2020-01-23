/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 20:43:38 by hessabra          #+#    #+#             */
/*   Updated: 2019/10/08 05:29:58 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		compteur(int i)
{
	int			n;
	int			j;

	j = 1;
	n = 0;
	if (i < 0)
	{
		j = 2;
		i = i * (-1);
	}
	while (i != 0)
	{
		i = i / 10;
		n++;
	}
	return (n + j);
}

static char		*wutret(int i)
{
	char		*c;

	if (i == 0)
	{
		c = "0";
		return (ft_strdup(c));
	}
	if (i == -2147483648)
	{
		c = "-2147483648";
		return (ft_strdup(c));
	}
	return (NULL);
}

static	int		signz(int i)
{
	int			z;

	z = 0;
	if (i < 0)
		z = -1;
	return (z);
}

static void		len(int j, int z, char *ret)
{
	if (z == -1)
		ret[j] = '-';
}

char			*ft_itoa(int i)
{
	char		*ret;
	int			mod;
	int			n;
	int			z;

	if (i == 0 || i == -2147483648)
		return (wutret(i));
	n = compteur(i);
	z = signz(i);
	if (i < 0)
		i = i * (-1);
	ret = (char *)ft_mema(sizeof(char) * n);
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, (size_t)n);
	n = n - 2;
	while (i != 0)
	{
		mod = i % 10;
		ret[n] = mod + 48;
		i = i / 10;
		n--;
	}
	len(n, z, ret);
	return (ret);
}
