/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_expansion2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:18:13 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/16 00:47:20 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

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
	ptr = (char *)ft_mmalloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = c;
	ptr[++i] = '\0';
	return (ptr);
}

char	*ft_ret(char *line, char **tmp)
{
	ft_strdel(tmp);
	return (line);
}
