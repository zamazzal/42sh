/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 15:53:36 by hessabra          #+#    #+#             */
/*   Updated: 2018/10/11 13:01:34 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*x;

	x = (char *)s;
	if (c == '\0')
		return (x + (int)ft_strlen(s));
	i = 0;
	while (x[i])
	{
		if (x[i] == c)
			return (x + i);
		i++;
	}
	return (0);
}
