/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:13:53 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 11:33:54 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	get_type(int type)
{
	int typ2;

	if (!type)
		return (0);
	typ2 = 1;
	while (--type)
		typ2 *= 2;
	return (typ2);
}

static int	jobs_usage(char c)
{
	ft_putstr_fd("jobs: ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd(" invalide option.", 2);
	ft_putendl_fd("\tusage: jobs -[lp] jobspec ...", 2);
	return (-1);
}

int			get_option(char **argv, int *option)
{
	size_t i;
	size_t j;

	i = 0;
	while (argv[++i] && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] == 'l' || argv[i][j] == 'p')
			{
				(*option) &= ~(FLAGS_P | FLAGS_L);
				(*option) |= get_type(argv[i][j] - 96);
			}
			else
				return (jobs_usage(argv[i][j]));
			j++;
		}
	}
	return (i);
}
