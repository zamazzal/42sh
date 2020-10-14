/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_built_check4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:43:36 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/16 03:01:01 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_check_flag(void)
{
	int tmp;

	if (!g_readline->r && (g_readline->num1 >
				g_readline->num2 && g_readline->num2 != 0))
		g_readline->r = 1;
	else if (g_readline->r && (g_readline->num1
				< g_readline->num2 && g_readline->num1 != 0))
	{
		tmp = g_readline->num1;
		g_readline->num1 = g_readline->num2;
		g_readline->num2 = tmp;
		g_readline->r = 1;
	}
	else if (g_readline->r && (g_readline->num1
				> g_readline->num2 && g_readline->num1 != 0))
	{
		tmp = g_readline->num1;
		g_readline->num1 = g_readline->num2;
		g_readline->num2 = tmp;
		g_readline->r = 0;
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
		if (ft_strcmp(arg[i], "-l") && ft_strcmp(arg[i], "-n") && ft_strcmp(
			arg[i], "-r") && ft_strcmp(arg[i], "-e") && ft_strcmp(arg[i], "-s"))
			nbr++;
		else if (nbr > 0)
			nbr = 4;
		if (!ft_strcmp(arg[i], "-e") && (arg[i + 1] && arg[i + 1][0] != '-'))
			i++;
		i++;
	}
	if (nbr >= 3)
	{
		ft_putstr_fd("\nfc: too many arguments\n", 2);
		return (0);
	}
	return (1);
}

int		ft_built_editor(char **arg, int index)
{
	char *tmp;

	if (!arg[index])
		return (0);
	tmp = g_readline->editor;
	g_readline->editor = ft_strjoin(arg[index], " ");
	free(tmp);
	tmp = ft_strjoin(g_readline->editor, g_random_save);
	free(g_readline->editor);
	g_readline->editor = tmp;
	g_readline->e = 1;
	return (1);
}

int		ft_check_args3(char **arg, int i)
{
	if (!ft_strcmp(arg[i], "-l"))
		return (g_readline->l = 1);
	else if (!ft_strcmp(arg[i], "-n"))
		return (g_readline->n = 1);
	return (0);
}

int		ft_check_e(char **arg, int i)
{
	if (!ft_strcmp(arg[i], "-e") && !arg[i + 1])
	{
		ft_putstr_fd("\nfc: argument expected: -e\n", 2);
		return (0);
	}
	if (!g_readline->l)
		g_readline->e = 1;
	if (!arg[i + 2])
		g_readline->num1 = g_readline->indexfor_history - 1;
	if (!ft_built_editor(arg, i + 1))
		return (0);
	return (1);
}
