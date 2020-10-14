/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 07:24:50 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/02 22:27:30 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static uint	get_type(uint type)
{
	uint typ2;

	if (!type)
		return (0);
	typ2 = 1;
	while (--type)
		typ2 *= 2;
	return (typ2);
}

void		print_type_lower(uint type_lower, uint flag, va_list ap)
{
	if (print_type_lower1(type_lower, flag, ap))
		return ;
	if (print_type_lower2(type_lower, flag, ap))
		return ;
	if (print_type_lower3(type_lower, flag, ap))
		return ;
	if (print_point_adress(type_lower, flag, ap))
		return ;
}

void		print_type_upper(uint type_upper, uint flag, va_list ap)
{
	if (print_type_upper1(type_upper, flag, ap))
		return ;
}

size_t		get_conver(uint flag)
{
	size_t i;

	i = 1;
	if ((flag & LLINT) || (flag & SCHR))
		i += 2;
	if ((flag & SINT) || (flag & LINT))
		i += 1;
	return (i);
}

int			search_format(char *format, va_list ap)
{
	uint	type_lower;
	uint	type_upper;
	uint	flag;
	char	search;

	flag = 0;
	type_lower = 0;
	type_upper = 0;
	flag = get_flag(format);
	search = format[get_conver(flag)];
	if (ft_islower(search))
		type_lower = search - 96;
	else if (ft_isupper(search))
		type_upper = search - 64;
	type_lower = get_type(type_lower);
	type_upper = get_type(type_upper);
	if (type_lower)
		print_type_lower(type_lower, flag, ap);
	else if (type_upper)
		print_type_upper(type_upper, flag, ap);
	return (get_conver(flag) + 1);
}
