/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 15:19:53 by hessabra          #+#    #+#             */
/*   Updated: 2018/10/17 11:31:51 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	x;

	x = ft_strlen(dst);
	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j] != '\0' && i < (dstsize - 1) && dstsize != 0)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	if (x + ft_strlen(src) > ft_strlen(src) + dstsize)
		return (ft_strlen(src) + dstsize);
	return (x + ft_strlen(src));
}
