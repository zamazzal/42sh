/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putoctal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:09:51 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/02 22:30:03 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putoctal(t_ullint nbr)
{
	char	cnv;
	ushort	rest;

	if (nbr < 8)
	{
		cnv = nbr + '0';
		ft_putchar(cnv);
	}
	else
	{
		ft_putoctal(nbr / 8);
		rest = nbr % 8 + '0';
		ft_putchar(rest);
	}
}
