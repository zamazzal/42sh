/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_built_check3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:45:15 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/16 02:31:12 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_clear_file(void)
{
	ft_execute_editor();
	close(g_readline->file_fd);
}

int		ft_arg1(char **arg, int i)
{
	g_readline->num1 = (g_readline->indexfor_history) + ft_atoi(arg[i]);
	g_readline->num2 = (g_readline->indexfor_history) + ft_atoi(arg[i + 1]);
	if ((g_readline->num1 < 0 || g_readline->num2 < 0) || (g_readline->num1
		|| g_readline->num2) >= g_readline->indexfor_history)
	{
		ft_putstr_fd("\nfc: no such event: 0\n", 2);
		return (0);
	}
	return (1);
}

int		ft_check_args1(char **arg)
{
	int i;

	i = 0;
	while (arg[i++] != '\0')
	{
		if (arg[i])
		{
			if (arg[i][0] != '-' && (ft_atoi(arg[i]) && !arg[i + 1]))
				return (g_readline->num1 = ft_atoi(arg[i]));
			else if (arg[i] && arg[i + 1] && ((arg[i][0] != '-'
			&& arg[i + 1][0] != '-') && ft_atoi(arg[i]) && ft_atoi(arg[i + 1])))
			{
				g_readline->num1 = ft_atoi(arg[i]);
				g_readline->num2 = ft_atoi(arg[i + 1]);
				return (1);
			}
			else if ((arg[i][0] == '-' && ft_isdigit(arg[i][1])) && !arg[i + 1])
				return (ft_arg(arg, i) == 0 ? 0 : 1);
			else if (arg[i + 1] && ((arg[i][0] == '-' && arg[i + 1][0] == '-')
			&& (ft_isdigit(arg[i][1]) && ft_isdigit(arg[i + 1][1]))))
				return (ft_arg1(arg, i) == 0 ? 0 : 1);
		}
	}
	return (1);
}
