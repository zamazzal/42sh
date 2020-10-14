/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 07:53:32 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/02 22:27:54 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ret_one(const char *s1, char *s2)
{
	if (s1)
		return (ft_strdup(s1));
	if (s2)
		return (ft_strdup(s2));
	return (NULL);
}

char		*ft_strjoin(const char *str, char *str2)
{
	int			i;
	char		*fraiche;
	int			j;

	i = 0;
	j = 0;
	if (str == 0 || str2 == 0)
		return (ret_one(str, str2));
	if (!(fraiche = (char *)malloc((ft_strlen(str)
						+ ft_strlen(str2) + 1) * sizeof(char))))
		return (NULL);
	if (fraiche)
	{
		while (str[i])
		{
			fraiche[i] = str[i];
			i++;
		}
		while (str2[j])
			fraiche[i++] = str2[j++];
		fraiche[i] = '\0';
		return (fraiche);
	}
	return (0);
}
