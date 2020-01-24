/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 20:34:07 by zamazzal          #+#    #+#             */
/*   Updated: 2020/01/20 06:50:21 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void	ft_flagerror(char c)
{
	ft_putstr_fd("export: -", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("usage: export name[=word]... or export -p", 2);
}

static int	ft_notvalid(char *str)
{
	ft_putstr_fd("export: not an identifier: ", 2);
	ft_putendl_fd(str, 2);
	return (1);
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

int			ft_getexported(void)
{
	char	*value;
	char	*key;
	int		i;

	i = 0;
	while (g_environ[i])
	{
		key = ft_getkey(g_environ[i]);
		value = ft_getvalue(g_environ[i]);
		ft_putstr("export ");
		ft_putstr(key);
		ft_putchar('=');
		ft_putchar('\"');
		ft_putstr(value);
		ft_putchar('\"');
		ft_putchar('\n');
		ft_strdel(&key);
		ft_strdel(&value);
		i++;
	}
	return (0);
}

int			ft_getexported_one(char **argv)
{
	int		i;
	char	*value;

	i = 0;
	while (argv[i])
	{
		value = ft_getenv(argv[i]);
		if (!value)
		{
			ft_putstr_fd("export: no such variable: ", 2);
			ft_putendl_fd(argv[i], 2);
			return (1);
		}
		ft_putstr("export ");
		ft_putstr(argv[i]);
		ft_putchar('=');
		ft_putchar('\"');
		ft_putstr(value);
		ft_putchar('\"');
		ft_putchar('\n');
		i++;
	}
	return (0);
}

int		check_identifier(char *str)
{
	int i;

	i = 0;
	if (str[i] == '\0' || (str[i] != '_' && !ft_isalpha(str[i])))
		return (1);
	i++;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int				ft_exportone(char *str)
{
	char *key;
	char *value;

	key = ft_getkey(str);
	if (*key == '\0')
		return (1);
	if (check_identifier(key))
	{
		ft_notvalid(key);
		ft_strdel(&key);
		return (1);
	}
	value = ft_getvalue(str);
	ft_setitern(key, value);
	ft_setenv(key, value);
	ft_strdel(&key);
	ft_strdel(&value);
	return (0);
}

static int		ft_setexport(char **argv)
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

int				ft_export(int argc, char **argv)
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
