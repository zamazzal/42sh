/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_existintab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 23:22:37 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/10 23:22:49 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_existintab(char **tab, char *str)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (ft_strequ(tab[i], str))
			return (1);
		i++;
	}
	return (0);
}
