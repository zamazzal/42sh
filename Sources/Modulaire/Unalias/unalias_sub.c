/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:39:23 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/10 13:44:50 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/alias_unalias.h"

int				ft_unaliasoption(char *arg)
{
	int		i;
	int		tiret;

	i = 1;
	tiret = 1;
	while (arg[i])
	{
		if (arg[i] == '-' && arg[i + 1])
		{
			ft_putstr_fd("42sh: unalias: --: invalid option\n", 2);
			ft_putstr_fd("unalias: usage: unalias [-a] name [name ...]\n", 2);
			return (0);
		}
		if (arg[i] != 'a')
		{
			ft_putstr_fd("42sh: unalias: -", 2);
			ft_putchar_fd(arg[i], 2);
			ft_putstr_fd(": invalid option\n", 2);
			ft_putstr_fd("unalias: usage: unalias [-a] name [name ...]\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}
