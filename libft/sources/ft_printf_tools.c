/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 22:20:07 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/02 22:25:43 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint	get_flag(char *format)
{
	uint flag;

	flag = 0;
	if (!ft_strncmp("%hh", format, 3))
		flag = SCHR;
	else if (!ft_strncmp("%h", format, 2))
		flag = SINT;
	else if (!ft_strncmp("%ll", format, 3))
		flag = LLINT;
	else if (!ft_strncmp("%l", format, 2))
		flag = LINT;
	return (flag);
}

void	put_cast(t_vars vars, uint flag)
{
	if ((flag & SCHR))
		ft_putnbr((t_schar)vars.ll);
	else if ((flag & SINT))
		ft_putnbr((t_sint)vars.ll);
	else if ((flag & LINT))
		ft_putnbr((t_lint)vars.ll);
	else if ((flag & LLINT))
		ft_putnbr((t_llint)vars.ll);
}

void	put_cast_ui(t_vars vars, uint flag)
{
	if ((flag & SCHR))
		ft_putnbr((t_uchar)vars.ui);
	else if ((flag & SINT))
		ft_putnbr((t_usint)vars.ui);
	else if ((flag & LINT))
		ft_putnbr((t_ulint)vars.ui);
	else if ((flag & LLINT))
		ft_putnbr((t_ullint)vars.ui);
}
