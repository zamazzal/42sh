/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_built_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:43:11 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/16 02:43:54 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		hist_norm(char *arg)
{
	g_readline->editor = ft_strdup(g_readline->history[get_hist_num(arg)]);
	return (1);
}

int		ft_check_s1(char **arg)
{
	int i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (!ft_strcmp(arg[i], "-s"))
		{
			if (arg[i + 1] && (arg[i + 1][0] == '-'
			&& ft_isdigit(arg[i + 1][1])))
			{
				if ((g_readline->indexfor_history + ft_atoi(arg[i + 1])) >= 0)
					g_readline->editor = g_readline->history
					[g_readline->indexfor_history + ft_atoi(arg[i + 1])];
				return (1);
			}
			else if (arg[i + 1] && !ft_isdigit(arg[i + 1][0]))
			{
				if (get_hist_num(arg[i + 1]) >= 0)
					return (hist_norm(arg[i + 1]));
			}
		}
		i++;
	}
	return (0);
}

void	ft_strdp1(void)
{
	g_readline->editor = ft_strdup(g_readline->history
	[g_insert->indexfor_history - 1]);
}

void	ft_strdp2(char **arg, int i)
{
	g_readline->editor = ft_strdup(g_readline->history[ft_atoi(arg[i + 1])]);
}

int		ft_check_s(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (!ft_strcmp(arg[i], "-s"))
		{
			if (arg[i + 1] && ft_check_eq(arg[i + 1]))
				return (1);
			if (!arg[i + 1])
			{
				if (g_readline->indexfor_history - 1 >= 0)
					ft_strdp1();
				return (1);
			}
			else if (arg[i + 1] && ft_isdigit(arg[i + 1][0]))
			{
				if (ft_atoi(arg[i + 1]) < g_readline->indexfor_history)
					ft_strdp2(arg, i);
				return (1);
			}
		}
		i++;
	}
	return (ft_check_s1(arg));
}
