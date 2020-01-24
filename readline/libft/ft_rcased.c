/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rcased.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:31:43 by hessabra          #+#    #+#             */
/*   Updated: 2019/03/10 05:34:56 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_cased.h"

char	*ft_strrv(char *dest, const char *src)
{
	int		i;
	int		j;
	char	*tmp;

	j = ft_strlen(dest);
	tmp = ft_strsub(src, 0, j);
	i = ft_strlen(tmp);
	while (i != -1)
	{
		dest[j] = tmp[i];
		i--;
		j--;
	}
	free(tmp);
	return (dest);
}

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
