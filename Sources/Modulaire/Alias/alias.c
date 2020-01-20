/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:26:33 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/20 05:48:16 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/alias_unalias.h"

static void		ft_aliasoptionp(char **all_aliases, char **arg,
													int *i, int *return_value)
{
	int		optionp;

	optionp = *i;
	while (!*return_value && arg[*i] && arg[*i][0] == '-')
	{
		*return_value = ft_aliasoption(arg[*i]);
		(*i)++;
	}
	if (!*return_value && *i != optionp)
		ft_putaliases(all_aliases, -1);
}

int				alias(char **arg, char ***all_aliases)
{
	int		i;
	int		return_value;

	return_value = 0;
	if (ft_tablen(arg) == 1)
		ft_putaliases(*all_aliases, -1);
	else
	{
		i = 1;
		ft_aliasoptionp(*all_aliases, arg, &i, &return_value);
		while (!return_value && arg[i])
		{
			ft_addalias(arg[i], all_aliases);
			i++;
		}
	}
	return (return_value);
}
