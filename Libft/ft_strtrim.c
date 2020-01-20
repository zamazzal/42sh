/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 00:15:02 by hessabra          #+#    #+#             */
/*   Updated: 2019/06/11 18:16:39 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ifin(const char *s)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s);
	j = i - 1;
	while (s[j] == ' ' || s[j] == '\t' || s[j] == '\n')
		j--;
	return (i - j - 1);
}

char			*ft_strtrim(char const *s)
{
	int		i;
	int		x;
	char	*cha;
	int		c;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	if (s[i] == '\0')
		return (ft_strdup("\0"));
	x = ifin(s);
	cha = ft_strnew(ft_strlen(s) - i - x);
	if (cha == NULL)
		return (NULL);
	c = 0;
	while (i < (ft_strlen(s) - x))
	{
		cha[c] = s[i];
		c++;
		i++;
	}
	return (cha);
}
