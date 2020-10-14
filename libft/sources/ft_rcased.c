/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rcased.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:31:43 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/29 20:13:03 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcp(char *dest, const char *src, int a)
{
	int		i;
	int		j;
	int		b;

	b = a;
	i = 0;
	j = ft_strlen(src);
	while (i < j)
	{
		dest[b] = src[i];
		i++;
		b++;
	}
	return (dest);
}

char	sign(int x)
{
	if (x > 0)
		return ('+');
	return ('-');
}
