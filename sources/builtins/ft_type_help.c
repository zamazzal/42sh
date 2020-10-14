/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:28:35 by kbahrar           #+#    #+#             */
/*   Updated: 2020/02/16 02:25:17 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		*ft_getalias(char *key)
{
	int		index;
	char	*alias;
	int		i;
	char	**split;

	alias = NULL;
	index = ft_aliasexist(key, g_all_aliases);
	i = 0;
	if (g_all_aliases)
	{
		while (g_all_aliases[i])
		{
			if (i == index)
				alias = g_all_aliases[i];
			i++;
		}
	}
	if (!alias)
		return (NULL);
	split = ft_strsplit(alias, '=');
	if (split[1])
		alias = ft_strdup(split[1]);
	ft_freetable(&split);
	return (alias);
}

int			if_alias(char *str, int flag)
{
	char	*alias;

	alias = ft_getalias(str);
	if (alias && flag == 0)
	{
		ft_strdel(&alias);
		return (0);
	}
	else if (alias && flag != 0)
	{
		ft_putstr_plus(str, " is aliased to ");
		ft_putendl(alias);
		ft_strdel(&alias);
		return (0);
	}
	return (1);
}

char		*ft_checkifhashed(char *cmd)
{
	unsigned long	hash;

	hash = hash_calc(cmd);
	if (g_htable[hash])
	{
		if (ft_strequ(g_htable[hash]->cmd, cmd))
		{
			if (access(g_htable[hash]->content, F_OK | X_OK) == 0)
			{
				g_htable[hash]->hits++;
				return (g_htable[hash]->content);
			}
		}
	}
	return (NULL);
}

int			if_hashed(char *cmd, int flag)
{
	char	*hash;

	hash = ft_checkifhashed(cmd);
	if (hash && flag == 0)
		return (0);
	else if (hash && flag != 0)
	{
		ft_putstr_plus(cmd, " is hashed to (");
		ft_putstr_plus(hash, ")\n");
		return (0);
	}
	return (1);
}

int			type_error(char *str, int ret)
{
	ft_putstr_fd("42sh: type: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": not found", 2);
	return (ret);
}
