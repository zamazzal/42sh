/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:32:42 by hessabra          #+#    #+#             */
/*   Updated: 2020/02/15 16:10:21 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			ft_putaliases(char **all_aliases, int index)
{
	int		i;

	i = 0;
	if (all_aliases)
		while (all_aliases[i])
		{
			if (index == -1)
			{
				ft_putstr("alias ");
				ft_putstr(all_aliases[i]);
			}
			else if (i == index)
			{
				ft_putstr("alias ");
				ft_putstr(all_aliases[i]);
			}
			i++;
			if (all_aliases[i] && index == -1)
				ft_putchar('\n');
		}
	ft_putchar('\n');
}

int				ft_aliasexist(char *alias, char **all_aliases)
{
	int		i;
	int		equ;
	int		alias_len;
	char	*tmp;

	if (all_aliases)
	{
		i = 0;
		alias_len = ft_strlen(alias);
		while (all_aliases[i])
		{
			tmp = ft_strsub(all_aliases[i], 0, alias_len);
			equ = ft_strequ(tmp, alias);
			ft_strdel(&tmp);
			if (equ)
				return (i);
			i++;
		}
	}
	return (-1);
}

int				ft_aliasoption(char *arg)
{
	int		i;
	int		tiret;

	i = 1;
	tiret = 1;
	while (arg[i])
	{
		if (arg[i] != 'p')
		{
			ft_putstr_fd("42sh: alias: -", 2);
			ft_putchar_fd(arg[i], 2);
			ft_putstr_fd(": invalid option\n", 2);
			ft_putstr_fd("alias: usage: alias [-p] [name[=value] ... ]\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int				ft_lentoequal(char *alias_arg)
{
	int		i;

	i = 0;
	while (alias_arg[i])
	{
		if (alias_arg[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

void			ft_addalias(char *alias_arg, char ***all_aliases)
{
	int		alias_len;
	int		index;
	char	*tmp;

	alias_len = ft_lentoequal(alias_arg);
	tmp = ft_strsub(alias_arg, 0, alias_len);
	if (alias_len)
	{
		if ((index = ft_aliasexist(tmp, *all_aliases)) >= 0)
			*all_aliases = ft_delfromtab(*all_aliases, index);
		alias_arg = ft_addquote(alias_arg);
		*all_aliases = ft_addtotab(*all_aliases, alias_arg);
	}
	else if ((index = ft_aliasexist(alias_arg, *all_aliases)) >= 0)
		ft_putaliases(*all_aliases, index);
	else
	{
		ft_putstr_fd("42sh: alias: ", 2);
		ft_putstr_fd(alias_arg, 2);
		ft_putstr_fd(": not found\n", 2);
	}
	ft_strdel(&alias_arg);
	ft_strdel(&tmp);
}
