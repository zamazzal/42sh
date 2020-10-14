/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:22:02 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/12 18:55:19 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char		**removein(char **table, char *find, int len)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	SAFE(new = (char **)ft_mmalloc(sizeof(char *) * ft_tablen(table)));
	while (table[i] != NULL)
	{
		if (!(ft_strinstr(table[i], find, len)))
		{
			new[j] = ft_strdup(table[i]);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	return (new);
}

void			ft_removeenv(char *name)
{
	char	**new;
	char	*find;
	char	**tmp;

	if (ft_strequ(name, "PATH"))
		ft_freeh_htab();
	find = ft_strjoin(name, "=");
	new = removein(g_environ, find, ft_strlen(find));
	tmp = g_environ;
	g_environ = new;
	ft_freetable(&tmp);
	ft_strdel(&find);
}

void			ft_removeintern(char *name)
{
	char	**new;
	char	*find;
	char	**tmp;

	if (ft_strequ(name, "PATH"))
		ft_freeh_htab();
	find = ft_strjoin(name, "=");
	new = removein(g_intern, find, ft_strlen(find));
	tmp = g_intern;
	g_intern = new;
	ft_freetable(&tmp);
	ft_strdel(&find);
}

int				ft_unset(int argc, char **argv)
{
	int		i;

	if (argc <= 1)
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		return (1);
	}
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_getenv(argv[i]))
			ft_removeenv(argv[i]);
		if (ft_getintern(argv[i]))
			ft_removeintern(argv[i]);
		i++;
	}
	return (0);
}
