/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_instr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:30:26 by zamazzal          #+#    #+#             */
/*   Updated: 2020/01/20 06:50:46 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		check_var_ster(char *str)
{
	int i;

	i = 0;
	if (str[i] == '\0' || (str[i] != '_' && !ft_isalpha(str[i])))
		return (1);
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (0);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (1);
}

int		ft_check_var_temp(int argc, char **argv)
{
	int i;

	i = 0;
	while (i < argc)
	{
		if (check_var_ster(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int		ft_seter(char *str)
{
	char *key;
	char *value;

	key = ft_getkey(str);
	value = ft_getvalue(str);
	ft_setenv(key, value);
	ft_strdel(&key);
	ft_strdel(&value);
	return (0);
}

int		ft_seter2(char *str)
{
	char *key;
	char *value;

	key = ft_getkey(str);
	value = ft_getvalue(str);
	ft_setitern(key, value);
	ft_strdel(&key);
	ft_strdel(&value);
	return (0);
}

int		ft_tempvar(char **argv, char **back_env)
{/*
	if (!(ft_builtins(argv, info)))
	{
		ft_freetable(&back_env);
		return (1);
	}*/
	ft_freetable(&g_environ);
	g_environ = back_env;
	return (2);
}

int		checkifseter(char **argv)
{
	char	**back_env;
	int		i;

	i = 0;
	if (check_var_ster(argv[0]))
		return (0);
	if (ft_check_var_temp(ft_tablen(argv), argv))
	{
		back_env = ft_tabdup(g_environ);
		while (argv[i])
		{
			if (!check_var_ster(argv[i]))
				ft_seter(argv[i]);
			else
				return (ft_tempvar(&argv[i], back_env));
			i++;
		}
	}
	else
	{
		while (argv[i])
			ft_seter2(argv[i++]);
	}
	return (2);
}
