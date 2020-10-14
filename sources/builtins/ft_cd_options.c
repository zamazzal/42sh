/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <kbahrar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 18:17:36 by kbahrar           #+#    #+#             */
/*   Updated: 2020/01/13 15:17:34 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void	init_options(int *opt)
{
	int		i;

	i = 0;
	while (i < 3)
		opt[i++] = -1;
}

static int	get_options(int *opt, char *str)
{
	int		i;

	i = 0;
	while (str[++i])
	{
		init_options(opt);
		if (str[i] == 'P')
			opt[0] = 1;
		else if (str[i] == 'L')
			opt[1] = 1;
		else
		{
			ft_putstr_fd("42sh: type: -", 2);
			ft_putchar_fd(str[i], 2);
			ft_putendl_fd(": invalid option\ntype: usage:[-LP][name]", 2);
			return (-1);
		}
	}
	return (0);
}

int			ft_cd_options(int *opt, int *place, char **args)
{
	int		i;
	int		flag;

	init_options(opt);
	i = 1;
	flag = 0;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1] == '-' && !args[i][2])
		{
			*place = i + 1;
			break ;
		}
		if (args[i][0] == '-' && args[i][1])
			flag = get_options(opt, args[i]);
		else
			break ;
		if (flag == -1)
			return (1);
		i++;
		*place = i;
	}
	return (0);
}
