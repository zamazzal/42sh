/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_expansion2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:18:13 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/21 12:19:48 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		add_to(char *line, int i)
{
	int	j;

	j = 1;
	while (line[i] != '\0' && line[i] != ' ')
	{
		i++;
		j++;
	}
	return (j);
}

char	*ft_charjoin(char *str, char c)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = c;
	ptr[++i] = '\0';
	return (ptr);
}
