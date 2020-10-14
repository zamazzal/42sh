/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addtotab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:09:17 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/12 18:49:27 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_addtotab(char **table, char *line)
{
	char	**new;
	char	**tmp;
	int		len;
	int		i;

	tmp = table;
	if (table)
		len = ft_tablen(table) + 1;
	else
		len = 1;
	new = (char**)ft_mmalloc(sizeof(char*) * (len + 1));
	*(new + len) = 0;
	i = 0;
	while (table && *(table + i))
	{
		*(new + i) = ft_strdup(*(table + i));
		i++;
	}
	*(new + i) = ft_strdup(line);
	*(new + i + 1) = 0;
	dfre(tmp);
	return (new);
}
