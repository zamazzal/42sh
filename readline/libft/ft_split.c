/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 05:07:26 by hessabra          #+#    #+#             */
/*   Updated: 2019/10/08 05:29:58 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int			nbr_ltr(char *s, char *c)
{
	int			nbr_char;

	nbr_char = ft_strlen(s);
	if ((s = ft_strstr(s, c)))
		nbr_char = nbr_char - ft_strlen(s);
	return (nbr_char);
}

static int			nbr_wrd(const char *s, char *c)
{
	int		nbrwrd;

	nbrwrd = 0;
	while ((s = ft_strstr(s, c)))
	{
		s = s + 2;
		nbrwrd++;
	}
	return (nbrwrd);
}

static void			cpy(char **chaine, char *s, char *c)
{
	int		j;

	j = 0;
	while (ft_strcmp(s, ft_strstr(s, c)) && *s)
	{
		(*chaine)[j] = *s;
		j++;
		s++;
	}
	(*chaine)[j] = '\0';
}

static void			ft_racc(char *str, char *s, int *len, char **chaine)
{
	*len = nbr_ltr((char *)str, s);
	*chaine = (char *)ft_mema(sizeof(char) * (*len + 1));
	if (*chaine == NULL)
		return ;
	cpy(&(*chaine), str, s);
}

char				**ft_split(char *str, char *s)
{
	char		**chaine;
	int			i;
	int			len;
	int			wrd;

	if (s == NULL)
		return (NULL);
	wrd = nbr_wrd(str, s);
	chaine = (char **)ft_mema(sizeof(char *) * (wrd + 1));
	if (chaine == NULL)
		return (NULL);
	i = 0;
	while (i < wrd)
	{
		len = ft_strlen(s);
		while (!(ft_strcmp(str, ft_strstr(str, s))) && *str)
			str += len;
		if (*str == '\0')
			break ;
		ft_racc(str, s, &len, &(chaine[i]));
		str = str + len;
		i++;
	}
	chaine[i] = 0;
	return (chaine);
}
