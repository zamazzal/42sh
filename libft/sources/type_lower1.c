/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_lower1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 10:41:51 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/02 22:25:04 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_type_lower1(uint type_lower, uint flag, va_list ap)
{
	char			*str;
	t_vars			vars;

	if ((type_lower & D))
	{
		vars.ll = va_arg(ap, t_llint);
		if (!flag)
			ft_putnbr((int)vars.ll);
		else
			put_cast(vars, flag);
	}
	else if ((type_lower & S))
	{
		str = va_arg(ap, char*);
		ft_putstr(str);
	}
	else if ((type_lower & C))
	{
		vars.c = va_arg(ap, int);
		ft_putchar(vars.c);
	}
	else
		return (0);
	return (1);
}

int	print_type_lower2(uint type_lower, uint flag, va_list ap)
{
	t_vars	vars;

	if ((type_lower & I) || (type_lower & U))
	{
		vars.ui = va_arg(ap, t_ullint);
		if (!flag)
			ft_putuint((uint)vars.ui);
		else
			put_cast_ui(vars, flag);
	}
	else if ((type_lower & X))
	{
		vars.ui = va_arg(ap, t_ullint);
		if (!flag)
			ft_puthexa((uint)vars.ui, 39);
		else if (flag & SINT)
			ft_puthexa((t_usint)vars.ui, 39);
		else if (flag & LINT)
			ft_puthexa((t_ulint)vars.ui, 39);
		else if (flag & LLINT)
			ft_puthexa((t_ullint)vars.ui, 39);
	}
	else
		return (0);
	return (1);
}

int	print_type_lower3(uint type_lower, uint flag, va_list ap)
{
	t_vars	vars;

	(void)flag;
	if ((type_lower & O))
	{
		vars.ui = va_arg(ap, t_ullint);
		if (!flag)
			ft_putoctal((uint)vars.ui);
		else if (flag & SCHR)
			ft_putoctal((t_schar)vars.ui);
		else if (flag & SINT)
			ft_putoctal((t_usint)vars.ui);
		else if (flag & LINT)
			ft_putoctal((t_ulint)vars.ui);
		else if (flag & LLINT)
			ft_putoctal((t_ullint)vars.ui);
	}
	else
		return (0);
	return (1);
}

int	print_point_adress(uint type_lower, uint flag, va_list ap)
{
	t_vars vars;

	(void)flag;
	if ((type_lower & P))
	{
		vars.ui = va_arg(ap, t_ullint);
		ft_putstr("0x7fff");
		ft_puthexa((t_ullint)vars.ui, 7);
	}
	else
		return (0);
	return (1);
}
