/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 11:09:41 by hessabra          #+#    #+#             */
/*   Updated: 2018/10/11 21:50:18 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*x;
	unsigned char	*y;
	size_t			i;
	unsigned char	r;

	i = 0;
	r = (unsigned char)c;
	x = (unsigned char *)src;
	y = (unsigned char *)dest;
	while (i < n)
	{
		y[i] = x[i];
		if (y[i] == r)
			return ((unsigned char *)(y + i + 1));
		i++;
	}
	return (NULL);
}
