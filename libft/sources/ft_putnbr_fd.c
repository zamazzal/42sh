/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 23:44:53 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/02 22:30:36 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(t_llint n, int fd)
{
	t_ullint	nb;
	char		a;

	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	nb = n;
	if (nb < 10)
	{
		a = nb + '0';
		ft_putchar_fd(a, fd);
	}
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		a = nb % 10 + '0';
		ft_putchar_fd(a, fd);
	}
}
