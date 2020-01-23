/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_built_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:09:19 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/21 15:47:23 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_check_flag(void)
{
	if (!g_readline->r && (g_readline->num1 >
	g_readline->num2 && g_readline->num2 != 0))
	{
		ft_putendl("\nfc: history events can't be executed backwards, aborted");
		return (-1);
	}
	if (g_readline->r && (g_readline->num1
	< g_readline->num2 && g_readline->num1 != 0))
	{
		ft_putendl("\nfc: history events can't be executed backwards, aborted");
		return (-1);
	}
	ft_putchar('\n');
	return (1);
}

int		ft_arg_nbr(char **arg)
{
	int	i;
	int	nbr;

	i = 1;
	nbr = 0;
	while (arg[i])
	{
		if (ft_strcmp(arg[i], "-l") && ft_strcmp(arg[i], "-n") &&
		ft_strcmp(arg[i], "-r") && ft_strcmp(arg[i], "-e"))
			nbr++;
		else if (nbr > 0)
			nbr = 4;
		if ((arg[i][0] == '-' && !ft_isdigit(arg[i][1]))
		&& (ft_strcmp(arg[i], "-l") && ft_strcmp(arg[i], "-n")
		&& ft_strcmp(arg[i], "-r") && ft_strcmp(arg[i], "-e")))
			nbr = 4;
		i++;
	}
	if (nbr >= 3)
	{
		ft_putstr("\nfc: too many arguments");
		return (0);
	}
	return (1);
}

int		ft_built_editor(char **arg, int index)
{
	if (!arg[index])
		return (0);
	if (!ft_strcmp(arg[index], "vim"))
		g_readline->editor = ft_strdup("/usr/bin/vim");
	else if (!ft_strcmp(arg[index], "nano"))
		g_readline->editor = ft_strdup("/usr/bin/nano");
	else if (!ft_strcmp(arg[index], "emacs"))
		g_readline->editor = ft_strdup("/usr/bin/emacs");
	else
	{
		ft_putstr("\ncommand not found: ");
		ft_putstr(arg[index]);
		return (0);
	}
	g_readline->e = 1;
	return (1);
}

int		ft_check_args(char **arg)
{
	int i;

	i = 0;
	while (arg[i++] != '\0')
	{
		if (!ft_strcmp(arg[i], "-r"))
			g_readline->r = 1;
		if (!ft_strcmp(arg[i], "-e"))
			return (ft_built_editor(arg, i + 1));
		if (!ft_strcmp(arg[i], "-n"))
			g_readline->n = 1;
		if (!ft_strcmp(arg[i], "-l"))
			g_readline->l = 1;
		if (arg[i][0] != '-' && !arg[i + 1])
			return (g_readline->num1 = ft_atoi(arg[i]));
		else if (arg[i][0] != '-' && ((arg[i + 1] &&
		arg[i + 1][0] != '-') && !arg[i + 2]))
		{
			g_readline->num1 = ft_atoi(arg[i]);
			g_readline->num2 = ft_atoi(arg[i + 1]);
			return (1);
		}
	}
	return (0);
}

void	ft_clear_file(void)
{
	ft_execute_editor();
	g_readline->file_fd = open("random_save", O_TRUNC);
}
