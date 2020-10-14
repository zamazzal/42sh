/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_upper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:31:27 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/02 22:09:28 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_type_upper1(uint type_upper, uint flag, va_list ap)
{
	t_vars vars;

	ft_putnbr(type_upper);
	ft_putchar('\n');
	if ((type_upper & XX))
	{
		vars.ui = va_arg(ap, t_ullint);
		if (!flag)
			ft_puthexa((uint)vars.ui, 7);
		else if (flag & SINT)
			ft_puthexa((t_usint)vars.ui, 7);
		else if (flag & LINT)
			ft_puthexa((t_ulint)vars.ui, 7);
		else if (flag & LLINT)
			ft_puthexa((t_ullint)vars.ui, 7);
	}
	else
		return (0);
	return (1);
}
