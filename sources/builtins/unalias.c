/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:14:56 by hessabra          #+#    #+#             */
/*   Updated: 2020/02/15 16:14:23 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		ft_unaliasoptiona(char ***all_aliases, char **arg,
													int *i, int *return_value)
{
	int		option_a;

	option_a = *i;
	while (!*return_value && arg[*i] && arg[*i][0] == '-')
	{
		*return_value = ft_unaliasoption(arg[*i]);
		(*i)++;
	}
	if (!*return_value && *i != option_a)
	{
		dfre(*all_aliases);
		*all_aliases = (char **)ft_mmalloc(sizeof(char *));
		*all_aliases[0] = 0;
	}
	else if (!*return_value && *i > 1 && !arg[(*i) + 1])
	{
		ft_putstr_fd("unalias: usage: unalias [-a] name [name ...]\n", 2);
		*return_value = 1;
	}
}

static void		ft_managearg(int *return_value, char *arg, char ***all_aliases)
{
	int		index;

	if ((index = ft_aliasexist(arg, *all_aliases)) >= 0)
		*all_aliases = ft_delfromtab(*all_aliases, index);
	else
	{
		ft_putstr_fd("42sh: unalias: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not found\n", 2);
		*return_value = -1;
	}
}

int				unalias(char **arg, char ***all_aliases)
{
	int		i;
	int		return_value;

	return_value = 0;
	if (ft_tablen(arg) == 1)
	{
		ft_putstr_fd("unalias: usage: unalias [-a] name [name ...]\n", 2);
		return (1);
	}
	else
	{
		i = 1;
		ft_unaliasoptiona(all_aliases, arg, &i, &return_value);
		while (return_value != 1 && arg[i] && ft_tablen(*all_aliases))
		{
			ft_managearg(&return_value, arg[i], all_aliases);
			i++;
		}
	}
	return (ft_entier(return_value));
}
