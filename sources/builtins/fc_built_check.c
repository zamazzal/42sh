/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_built_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:09:19 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/16 03:03:59 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_badop(char *arg)
{
	ft_putstr_fd("\nbad option: ", 2);
	ft_putendl_fd(arg, 2);
	return (0);
}

int		ft_check_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i++] != '\0')
	{
		if (arg[i])
		{
			if (ft_check_args3(arg, i))
				continue ;
			if (!ft_strcmp(arg[i], "-e") && g_readline->l != 1)
			{
				if (!ft_check_e(arg, i))
					return (0);
			}
			else if (!ft_strcmp(arg[i], "-r"))
				g_readline->r = 1;
			else if (ft_strcmp(arg[i], "-s") &&
					(arg[i][0] == '-' && !ft_isdigit(arg[i][1])))
				return (ft_badop(arg[i]));
			else if (!ft_check_editor(arg[i]) && !ft_check_args2(arg, i))
				return (0);
		}
	}
	return (1);
}

int		get_hist_num(char *arg)
{
	int	i;

	i = 0;
	i = g_readline->indexfor_history - 1;
	while (i >= 0)
	{
		if (ft_strstr(g_readline->history[i], arg))
			return (i);
		i--;
	}
	return (-1);
}

int		ft_check_args2(char **arg, int i)
{
	if (arg[i])
	{
		if (arg[i][0] != '-' && !ft_atoi(arg[i]))
		{
			g_readline->num1 = get_hist_num(arg[i]);
			if (g_readline->num1 >= 0)
				return (g_readline->num1);
			else
			{
				ft_strdel(&g_readline->editor);
				ft_putstr_fd("\nfc : Not found in history\n", 2);
				return (0);
			}
		}
	}
	return (1);
}

int		ft_arg(char **arg, int i)
{
	g_readline->num1 = (g_readline->indexfor_history - 1) + ft_atoi(arg[i]);
	if (g_readline->num1 < 0 || g_readline->num1
			>= g_readline->indexfor_history)
	{
		ft_putstr_fd("\nfc: no such event: 0\n", 2);
		return (0);
	}
	return (1);
}
