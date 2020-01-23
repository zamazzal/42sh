/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 18:30:35 by hessabra          #+#    #+#             */
/*   Updated: 2018/10/11 12:47:32 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		i = k;
		j = 0;
		while (needle[j] == haystack[i] && i < len)
		{
			if (!(needle[j + 1]))
				return ((char *)(haystack + i - j));
			i++;
			j++;
		}
		k++;
	}
	return (0);
}
