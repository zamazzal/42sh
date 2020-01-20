/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 22:13:01 by hessabra          #+#    #+#             */
/*   Updated: 2018/10/15 03:26:30 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*x;
	unsigned const char	*y;
	size_t				i;

	i = 0;
	x = (unsigned const char *)s1;
	y = (unsigned const char *)s2;
	while (i < n)
	{
		if (x[i] != y[i])
			return ((int)x[i] - (int)y[i]);
		i++;
	}
	return (0);
}
