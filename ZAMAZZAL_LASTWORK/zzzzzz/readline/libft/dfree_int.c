/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfree_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 03:03:00 by hessabra          #+#    #+#             */
/*   Updated: 2019/10/11 03:51:11 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		dfree_int(int **nbr)
{
	int		i;

	if (nbr)
	{
		i = 0;
		while (nbr[i] != NULL)
		{
			ft_nbrdel(&(nbr[i]));
			i++;
		}
		free(nbr);
		nbr = NULL;
	}
}
