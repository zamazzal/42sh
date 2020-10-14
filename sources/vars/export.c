/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 20:34:07 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/12 22:30:25 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			ft_notvalid(char *str)
{
	ft_putstr_fd("export: not an identifier: ", 2);
	ft_putendl_fd(str, 2);
	return (1);
}

static void	ft_flagerror(char c)
{
	ft_putstr_fd("export: -", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("usage: export name[=word]... or export -p", 2);
}

static int	ft_getflags(int argc, char **argv, int *mode)
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
			if (argv[i][j] == 'p')
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

static int	ft_setexport(char **argv)
{
	int		i;
	char	*value;

	i = 0;
	while (argv[i] != NULL)
	{
		if (ft_checkcinstr(argv[i], '='))
		{
			if (ft_exportone(argv[i]))
				return (1);
		}
		else
		{
			value = ft_getintern(argv[i]);
			if (check_identifier(argv[i]))
				return (ft_notvalid(argv[i]));
			ft_setenv(argv[i], value);
		}
		i++;
	}
	return (0);
}

int			ft_export(int argc, char **argv)
{
	int i;
	int mode;

	i = ft_getflags(argc, argv, &mode);
	if (i == -1)
		return (2);
	if (argc > 1)
	{
		if (mode)
		{
			if (!argv[i])
				return (ft_getexported());
			else
				return (ft_getexported_one(&argv[i]));
		}
		else
			return (ft_setexport(&argv[i]));
	}
	else
		ft_puttables(g_environ);
	return (0);
}
