/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 10:46:20 by hessabra          #+#    #+#             */
/*   Updated: 2018/10/07 00:23:31 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*x;
	const char	*y;
	size_t		i;

	x = (char *)dest;
	y = (const char *)src;
	i = 0;
	while (i < n)
	{
		x[i] = y[i];
		i++;
	}
	return (x);
}
