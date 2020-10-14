/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 18:56:58 by kbahrar           #+#    #+#             */
/*   Updated: 2020/02/15 18:05:04 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	ft_type_t(char *str, int ret, int *opt)
{
	extern char	**environ;

	if (!if_alias(str, 0))
	{
		ft_putstr("alias\n");
		if (opt[0] != 1)
			return (0);
	}
	if (if_builtin(str))
	{
		ft_putstr("builtin\n");
		if (opt[0] != 1)
			return (0);
	}
	str = access_file(environ, str);
	if ((ft_strchr(str, '/')) && !access(str, F_OK))
	{
		ft_strdel(&str);
		ft_putstr("file\n");
	}
	else
		return (ret);
	return (0);
}

static int	ft_type_p(char *str, int opt, int a, int ret)
{
	extern char	**environ;

	if (opt == 1 && a == -1)
		if (if_builtin(str) || !if_alias(str, 0))
			return (0);
	str = access_file(environ, str);
	if ((ft_strchr(str, '/')) && !access(str, F_OK))
	{
		ft_putendl(str);
		ft_strdel(&str);
	}
	else
		return (ret);
	return (0);
}

static int	ft_type_a(char *str, int ret)
{
	extern char	**environ;
	char		*cpy;

	if_alias(str, 1);
	if_hashed(str, 1);
	cpy = ft_strdup(str);
	if (if_builtin(str))
	{
		ft_putstr(str);
		ft_putendl(" is a shell builtin");
	}
	str = access_file(environ, str);
	if (ft_strchr(str, '/') && !access(str, F_OK))
	{
		ft_putstr_plus(cpy, " is ");
		ft_putendl(str);
		ft_strdel(&str);
	}
	else if (!if_builtin(str))
	{
		ft_strdel(&cpy);
		return (ret);
	}
	ft_strdel(&cpy);
	return (0);
}

static int	ft_type_n(char *str, int ret)
{
	extern char	**environ;
	char		*cpy;

	if (!if_alias(str, 1) || !if_hashed(str, 1))
		;
	else if (if_builtin(str))
		ft_putstr_plus(str, " is a shell builtin\n");
	else
	{
		cpy = ft_strdup(str);
		str = access_file(environ, str);
		if ((ft_strchr(str, '/')) && !access(str, F_OK))
		{
			ft_putstr_plus(cpy, " is ");
			ft_putendl(str);
			ft_strdel(&cpy);
			ft_strdel(&str);
		}
		else
		{
			free(cpy);
			return (type_error(str, ret));
		}
	}
	return (0);
}

int			ft_type(char **args)
{
	int		i;
	int		opt[5];
	int		ret;

	i = 1;
	ret = 1;
	if (!args[i])
		return (0);
	if (ft_type_options(opt, &i, args) != 0)
		return (2);
	while (args[i])
	{
		if (opt[3] == 1)
			ret = ft_type_t(args[i], ret, opt);
		else if (opt[2] == 1 || opt[4] == 1)
			ret = ft_type_p(args[i], opt[2], opt[0], ret);
		else if (opt[0] == 1)
			ret = ft_type_a(args[i], ret);
		else
			ret = ft_type_n(args[i], ret);
		i++;
	}
	return (ret);
}
