/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 23:24:23 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/15 18:15:40 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		hash(void)
{
	int	n;
	int i;

	i = 0;
	n = 0;
	while (i < HTABLE_SIZE)
	{
		if (g_htable[i] && g_htable[i]->content)
		{
			if (n == 0)
			{
				ft_putendl("hits\tcommand");
				n++;
			}
			ft_putnbr(g_htable[i]->hits);
			ft_putchar('\t');
			ft_putendl(g_htable[i]->content);
		}
		i++;
	}
	if (!n)
		ft_putendl("hash: hash table empty");
	return (0);
}

int				ft_sethash(char **argv)
{
	int		rtn;
	char	*cmd;
	int		i;

	i = 0;
	rtn = 0;
	while (argv[i])
	{
		cmd = ft_checkcmd(argv[i]);
		if (!cmd)
		{
			rtn = 1;
			ft_putstr_fd("hash: ", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd(": not found", 2);
		}
		else
		{
			ft_add_inhashtable(argv[i], cmd);
			ft_strdel(&cmd);
		}
		i++;
	}
	return (rtn);
}

static void		ft_flagerror(char c)
{
	ft_putstr_fd("hash: -", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("usage: hash [-r] [name ...]", 2);
}

static int		ft_getflags(int argc, char **argv, int *mode)
{
	int		i;
	int		j;
	int		x;

	*mode = 0;
	i = 1;
	x = 0;
	while (i < argc && argv[i][0] == '-' && ft_isprint(argv[i][1])
	&& !ft_strequ(argv[i], "--"))
	{
		j = 1;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] == 'r')
				*mode = 1;
			else
			{
				ft_flagerror(argv[i][j]);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (i);
}

int				ft_hash(int argc, char **argv)
{
	int mode;
	int i;

	i = ft_getflags(argc, argv, &mode);
	if (i == -1)
		return (2);
	if (argc > 1)
	{
		if (mode)
			ft_freeh_htab();
		return (ft_sethash(&argv[i]));
	}
	else
		hash();
	return (0);
}
