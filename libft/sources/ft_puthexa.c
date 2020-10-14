/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:16:24 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/02 22:10:39 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthexa(t_ullint nbr, ushort plus)
{
	ushort rest;

	if (nbr < 16)
	{
		if (nbr < 10)
			ft_putchar(nbr + '0');
		else
			ft_putchar(nbr + '0' + plus);
	}
	else
	{
		ft_puthexa(nbr / 16, plus);
		rest = nbr % 16;
		if (rest < 10)
			ft_putchar(rest + '0');
		else
			ft_putchar(rest + '0' + plus);
	}
}
