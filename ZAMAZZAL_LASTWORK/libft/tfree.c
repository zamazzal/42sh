/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tfree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 18:15:51 by hessabra          #+#    #+#             */
/*   Updated: 2019/10/11 00:52:46 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			tfree(char ***array)
{
	int			i;
	int			j;

	i = 0;
	while (array[i])
	{
		j = 0;
		dfre(array[i]);
		i++;
	}
	if (array)
	{
		free(array);
		array = NULL;
	}
}
