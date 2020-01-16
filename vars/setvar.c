/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:25:37 by zamazzal          #+#    #+#             */
/*   Updated: 2020/01/14 16:27:33 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char		**addenv(char **table, char *key, char *value, int len)
{
	int		i;
	char	**new;

	SAFE(new = (char **)malloc(sizeof(char*) * (len + 2)));
	new[len + 1] = NULL;
	i = 0;
	while (i < len)
	{
		new[i] = ft_strdup(table[i]);
		i++;
	}
	new[i++] = ft_makevar(key, value);
	ft_freetable(&table);
	table = new;
	return (table);
}

int				ft_changvar(char **table, char *key, char *value)
{
	char	*finder;
	int		f_len;
	int		i;
	char	*tmp;

	if (!table)
		return (0);
	finder = ft_strjoin(key, "=");
	f_len = ft_strlen(finder);
	i = 0;
	while (table[i])
	{
		if (ft_strinstr(table[i], finder, f_len))
		{
			tmp = table[i];
			table[i] = ft_makevar(key, value);
			ft_strdel(&tmp);
			ft_strdel(&finder);
			return (-1);
		}
		i++;
	}
	ft_strdel(&finder);
	return (i);
}

int		ft_setenv(char *name, char *content)
{
	int		len;

	if (ft_strequ(name, "PATH"))
		ft_freeh_htab();
	if ((len = ft_changvar(g_environ, name, content)) == -1)
		return (0);
	g_environ = addenv(g_environ, name, content, len);
	return (0);
}

int		ft_setitern(char *name, char *content)
{
	int		len;

	if (ft_strequ(name, "PATH"))
		ft_freeh_htab();
	if ((len = ft_changvar(g_intern, name, content)) == -1)
	{
		ft_changvar(g_environ, name, content);
		return (0);
	}
	g_intern = addenv(g_intern, name, content, len);
	return (0);
}
