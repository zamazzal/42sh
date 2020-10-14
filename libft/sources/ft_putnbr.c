/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 21:11:48 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/02 22:31:06 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr(t_llint nbr)
{
	t_ullint	n;
	char		a;

	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = nbr * -1;
	}
	n = nbr;
	if (n < 10)
	{
		a = n + 48;
		write(1, &a, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		a = n % 10 + '0';
		write(1, &a, 1);
	}
}
