/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 20:19:31 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/10 12:14:05 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*fraiche;
	int		i;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	fraiche = (char *)ft_mmalloc(sizeof(char) * (ft_strlen(s) + 1));
	if (fraiche == NULL)
		return (NULL);
	while (s[i])
	{
		fraiche[i] = f(s[i]);
		i++;
	}
	fraiche[i] = '\0';
	return (fraiche);
}
