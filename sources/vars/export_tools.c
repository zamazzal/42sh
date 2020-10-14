/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:28:27 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/16 05:09:08 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

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

int			check_identifier(char *str)
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

int			ft_exportone(char *str)
{
	char *key;
	char *value;

	key = ft_getkey(str);
	if (*key == '\0')
	{
		ft_strdel(&key);
		return (1);
	}
	if (check_identifier(key))
	{
		ft_notvalid(key);
		ft_strdel(&key);
		return (1);
	}
	value = ft_getvalue(str);
	ft_setenv(key, value);
	ft_strdel(&key);
	ft_strdel(&value);
	return (0);
}
