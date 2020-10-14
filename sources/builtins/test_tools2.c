/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:37:03 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/07 12:37:44 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			ft_checkop(char *str)
{
	if (!ft_strcmp(str, "-eq"))
		return (1);
	if (!ft_strcmp(str, "-ne"))
		return (2);
	if (!ft_strcmp(str, "-gt"))
		return (3);
	if (!ft_strcmp(str, "-ge"))
		return (4);
	if (!ft_strcmp(str, "-lt"))
		return (5);
	if (!ft_strcmp(str, "-le"))
		return (6);
	return (-1);
}

static int	ft_checknbr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_checkcalc(char *arg1, int r, char *arg2)
{
	int num1;
	int num2;

	num1 = ft_atoi(arg1);
	num2 = ft_atoi(arg2);
	if (r == 1)
		return (num1 == num2 ? 0 : 1);
	if (r == 1)
		return (num1 == num2 ? 0 : 1);
	if (r == 2)
		return (num1 != num2 ? 0 : 1);
	if (r == 3)
		return (num1 > num2 ? 0 : 1);
	if (r == 4)
		return (num1 >= num2 ? 0 : 1);
	if (r == 5)
		return (num1 < num2 ? 0 : 1);
	if (r == 6)
		return (num1 <= num2 ? 0 : 1);
	return (1);
}

int			ft_type_error(char *s1, char *s2)
{
	ft_putstr_fd("test: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putendl_fd(s2, 2);
	return (2);
}

int			ft_test3args(char **argv)
{
	int r;

	if (!ft_strcmp(argv[1], "="))
		return (ft_strcmp(argv[0], argv[2]));
	if (!(ft_strcmp(argv[1], "!=")))
		return (ft_return(ft_strcmp(argv[0], argv[2])));
	if ((r = ft_checkop(argv[1])) != -1)
	{
		if (ft_checknbr(argv[0]))
			return (ft_type_error(argv[0], ": integer expression expected"));
		if (ft_checknbr(argv[2]))
			return (ft_type_error(argv[2], ": integer expression expected"));
		return (ft_checkcalc(argv[0], r, argv[2]));
	}
	ft_type_error(argv[1], ": unary operator expected");
	return (2);
}
