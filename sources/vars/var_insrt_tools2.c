/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_insrt_tools2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 02:19:44 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/16 02:20:37 by zamazzal         ###   ########.fr       */
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
