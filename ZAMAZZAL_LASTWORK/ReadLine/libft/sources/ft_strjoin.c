/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 22:59:28 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/13 15:39:35 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*swap;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	swap = (char *)ft_mema(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (swap == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		swap[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		swap[i++] = *s2;
		s2++;
	}
	swap[i] = '\0';
	return (swap);
}
