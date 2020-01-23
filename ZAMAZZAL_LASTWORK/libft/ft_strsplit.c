/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 20:10:59 by hessabra          #+#    #+#             */
/*   Updated: 2019/10/08 05:29:58 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int			nbr_wrd(const char *s, char c)
{
	int			r;

	r = 0;
	while (*s)
	{
		if ((*s != c && *s != '\0') && (*(s + 1) == c || *(s + 1) == '\0'))
			r++;
		s++;
	}
	return (r);
}

static int			nbr_ltr(char *s, char c)
{
	int			nbr_char;

	nbr_char = 0;
	while (s[nbr_char] != c && s[nbr_char] != '\0')
		nbr_char++;
	return (nbr_char);
}

static void			cpy(char **chaine, const char **s, char c, int i)
{
	int		j;

	j = 0;
	while (**s != c && **s != '\0')
	{
		chaine[i][j] = **s;
		j++;
		(*s)++;
	}
	chaine[i][j] = '\0';
}

char				**ft_strsplit(char const *s, char c)
{
	char		**chaine;
	int			i;

	if (s == NULL)
		return (NULL);
	chaine = (char **)ft_mema(sizeof(char *) * (nbr_wrd(s, c) + 1));
	if (chaine == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s == '\0')
			break ;
		chaine[i] = (char *)ft_mema(sizeof(char) * (nbr_ltr((char *)s, c) + 1));
		if (chaine == NULL)
			return (NULL);
		cpy(chaine, &s, c, i);
		i++;
	}
	chaine[i] = 0;
	return (chaine);
}
