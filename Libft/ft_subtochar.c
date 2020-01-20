/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subtochar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:09:56 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/10 12:14:05 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_sub2char(char *str, int c)
{
	char		*bow;
	size_t		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	bow = (char *)ft_mmalloc(sizeof(char) * i + 1);
	if (bow)
	{
		i = 0;
		while (str[i] && str[i] != c)
		{
			bow[i] = str[i];
			i++;
		}
		bow[i] = '\0';
	}
	return (bow);
}
