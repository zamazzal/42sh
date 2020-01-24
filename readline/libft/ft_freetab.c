/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 11:30:18 by helmanso          #+#    #+#             */
/*   Updated: 2019/10/02 01:14:02 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_freetab(char ***table)
{
	char	**temp;

	if (!table || !(*table))
		return ;
	temp = *table;
	while (*temp)
		ft_strdel(&(*temp++));
	free(*table);
	*table = NULL;
}
