/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:34:15 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/12 22:37:59 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		checkbackslash(char *ptr, int i)
{
	int c;

	i--;
	c = 0;
	while (i >= 0)
	{
		if (ptr[i] == '\\')
			c++;
		if (ptr[i] != '\\')
			break ;
		i--;
	}
	return (c);
}

int		ft_strinstr(const char *s1, const char *s2, int len)
{
	int i;
	int j;

	if (!s1)
		return (0);
	if (s2[0] == '\0')
		return (1);
	i = 0;
	while ((s1[i] != '\0') && (i < len))
	{
		j = 0;
		while (s2[j] != '\0')
		{
			if (s1[i + j] != s2[j] || j + i >= len)
				break ;
			j++;
		}
		if (s2[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int		ft_checkcinstr(char *ptr, int c)
{
	int i;

	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == '\"')
		{
			i++;
			while (ptr[i] && ptr[i] != '\"')
				i++;
		}
		if (ptr[i] == '\'')
		{
			i++;
			while (ptr[i] && ptr[i] != '\'')
				i++;
		}
		if (ptr[i] == c && !(checkbackslash(ptr, i) % 2))
			return (1);
		i++;
	}
	return (0);
}

void	ft_puttables(char **table)
{
	size_t	i;

	i = 0;
	while (table[i] != NULL)
		ft_putendl(table[i++]);
}

char	*ft_strjoin_lite(char *s1, char const *s2)
{
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	if (!(ptr = (char*)ft_mmalloc((ft_strlen(s1) + ft_strlen(s2)) + 1)))
		return (NULL);
	ft_strcpy(ptr, s1);
	ft_strcat(ptr, s2);
	if (s1)
		ft_strdel(&s1);
	return (ptr);
}
