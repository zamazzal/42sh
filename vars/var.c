/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:28:54 by zamazzal          #+#    #+#             */
/*   Updated: 2020/01/14 16:30:08 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		ft_create_default_vars(void)
{
	ft_setitern("ZAMAZZAL1", "zamazzal");
	ft_setitern("ZAMAZZAL2", "zamazzal");
	ft_setitern("ZAMAZZAL3", "zamazzal");
	ft_setitern("ZAMAZZAL4", "zamazzal");
}

int				creation(void)
{
	extern char	**environ;
	char		*shlvl;

	SAFE(g_intern = (char **)malloc(sizeof(char *)));
	g_intern[0] = NULL;
	ft_create_default_vars();
	g_environ = ft_tabdup(environ);
	shlvl = ft_itoa(ft_atoi(ft_getenv("SHLVL")) + 1);
	ft_setenv("SHLVL", shlvl);
	ft_strdel(&shlvl);
	g_intern = ft_jointab(g_intern, g_environ);
	return (0);
}
