/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_searchnreplace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 22:32:35 by hessabra          #+#    #+#             */
/*   Updated: 2019/02/04 22:32:53 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_searchnreplace(char *str, int s, int r)
{
	int		i;
	char	*m;

	m = str;
	i = 0;
	while (m[i])
	{
		if (m[i] == (char)s)
		{
			if (i == 0)
				m = "\0";
			else
				m[i] = (char)r;
			return (m);
		}
		i++;
	}
	if (m == 0)
	{
		m[i] = (char)r;
		m[i + 1] = 0;
	}
	return (m);
}
