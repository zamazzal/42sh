/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:19:53 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/07 12:35:57 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			ft_return(int r)
{
	return (r != 0 ? 0 : 1);
}

static int	ft_test2args(char **argv)
{
	if (ft_strcmp(argv[0], "-z") == 0)
		return (ft_strlen(argv[0]) ? 1 : 0);
	return (ft_test(argv[1], argv[0]));
}

static int	ft_testreturn(int rtn, int mode)
{
	if (mode == 1)
		return (rtn == 1 ? 0 : 1);
	return (rtn);
}

int			ft_testerror(void)
{
	ft_putendl_fd("test: too many arguments", 2);
	return (2);
}

int			test(int argc, char **argv)
{
	int mode;

	mode = 0;
	if (argc >= 3)
	{
		if (!ft_strcmp(argv[1], "!"))
		{
			argc--;
			argv = &argv[2];
			mode = 1;
		}
		else
			argv = &argv[1];
	}
	if (argc == 2)
		return (ft_testreturn(!argv[0] ? 1 : 0, mode));
	else if (argc == 3)
		return (ft_testreturn(ft_test2args(&argv[0]), mode));
	else if (argc == 4)
		return (ft_testreturn(ft_test3args(argv), mode));
	else if (argc > 4)
		return (ft_testerror());
	return (ft_testreturn(1, mode));
}
