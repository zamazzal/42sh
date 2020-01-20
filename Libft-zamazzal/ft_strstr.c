/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 18:00:31 by hessabra          #+#    #+#             */
/*   Updated: 2018/10/11 12:41:17 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[k] != '\0')
	{
		i = k;
		j = 0;
		while (haystack[i] == needle[j])
		{
			if (!(needle[j + 1]))
				return ((char *)(haystack + i - j));
			j++;
			i++;
		}
		k++;
	}
	return (0);
}
