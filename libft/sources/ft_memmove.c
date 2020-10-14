/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:34:19 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/02 22:16:51 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	x;
	char	back[len + 1];
	char	*s1;
	char	*s2;

	x = 0;
	s1 = (char*)src;
	s2 = (char *)dst;
	while (x < len)
	{
		back[x] = s1[x];
		x++;
	}
	x = 0;
	while (x < len)
	{
		s2[x] = back[x];
		x++;
	}
	return (dst);
}
