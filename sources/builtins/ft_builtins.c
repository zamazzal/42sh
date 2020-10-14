/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 17:56:56 by kbahrar           #+#    #+#             */
/*   Updated: 2020/02/15 23:42:53 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	if_all_num(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int			ft_exejobs(int *j_force_ex)
{
	*j_force_ex = 1;
	ft_putendl_fd("42sh: There are stopped jobs.", 2);
	return (1);
}

int			ft_exit(char **args)
{
	static int	jobs_force_exit = 0;
	int			num;

	num = 0;
	if (g_shell_pid == getpid() && g_current_jobs && !jobs_force_exit)
		return (ft_exejobs(&jobs_force_exit));
	if (!args[1])
		exit(0);
	if (args[1] && args[2])
	{
		ft_putendl_fd("42sh: exit: too many arguments", 2);
		return (255);
	}
	if (!if_all_num(args[1]))
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		num = 255;
	}
	else
		num = ft_atoi(args[1]);
	exit(num);
}

int			ft_builtins(char **av)
{
	if (!ft_strcmp(av[0], "cd"))
		return (ft_cd(av));
	else if (!ft_strcmp(av[0], "echo"))
		return (ft_echo(av));
	else if (!ft_strcmp(av[0], "type"))
		return (ft_type(av));
	else if (!ft_strcmp(av[0], "export"))
		return (ft_export(ft_tablen(av), av));
	else if (ft_strequ(av[0], "test"))
		return (test(ft_tablen(av), av));
	else if (ft_strequ(av[0], "set"))
		return (ft_set());
	else if (ft_strequ(av[0], "unset"))
		return (ft_unset(ft_tablen(av), av));
	else if (ft_strequ(av[0], "hash"))
		return (ft_hash(ft_tablen(av), av));
	else if (ft_strequ(av[0], "alias"))
		return (alias(av, &g_all_aliases));
	else if (ft_strequ(av[0], "unalias"))
		return (unalias(av, &g_all_aliases));
	else if (!ft_strcmp(av[0], "true"))
		return (0);
	else if (!ft_strcmp(av[0], "false"))
		return (1);
	return (-1);
}
