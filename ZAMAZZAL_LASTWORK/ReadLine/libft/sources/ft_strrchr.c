/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 16:02:58 by hessabra          #+#    #+#             */
/*   Updated: 2018/10/11 13:22:55 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		x;
	char	*y;
	int		i;

	x = -1;
	i = 0;
	y = (char *)s;
	if (c == '\0')
		return (y + (int)ft_strlen(s));
	while (y[i])
	{
		if (y[i] == c)
			x = i;
		i++;
	}
	if (x >= 0)
		return (y + x);
	return (0);
}
