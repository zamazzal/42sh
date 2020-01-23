/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 19:07:17 by hessabra          #+#    #+#             */
/*   Updated: 2018/10/15 02:49:58 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*x;
	size_t			i;

	x = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (x[i] == (unsigned char)c)
			return ((void *)(x + i));
		i++;
	}
	return (0);
}
