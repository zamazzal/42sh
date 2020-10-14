/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_built_e.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:06:21 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/16 02:41:21 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_open_file(void)
{
	g_readline->file_fd = open(g_random_save, O_TRUNC | O_RDWR | O_CREAT
	, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
}

void	ft_check_num(void)
{
	if ((g_readline->num1 < 0 || g_readline->num1
	> g_readline->indexfor_history)
	|| (g_readline->num2 < 0 || g_readline->num2
	> g_readline->indexfor_history))
	{
		g_readline->num2 = 0;
		g_readline->num1 = g_readline->indexfor_history - 1;
	}
}

void	ft_execute_editor(void)
{
	if (g_readline->l)
		ft_strdel(&g_readline->editor);
	else if (!g_readline->e && !g_readline->l)
		g_readline->editor = ft_strjoin("vim ", g_random_save);
}

void	ft_hist_e(void)
{
	ft_check_num();
	ft_open_file();
	if (!g_readline->num2)
	{
		ft_putendl_fd(g_readline->history[g_readline->num1],
		g_readline->file_fd);
	}
	else
		while (g_readline->num1 <= g_readline->num2)
		{
			ft_putendl_fd(g_readline->history[g_readline->num1],
			g_readline->file_fd);
			g_readline->num1++;
		}
	ft_clear_file();
}

void	ft_hist_er(void)
{
	ft_check_num();
	ft_open_file();
	if (!g_readline->num2)
		ft_putendl_fd(g_readline->history[g_readline->num1],
		g_readline->file_fd);
	else
	{
		while (g_readline->num1 >= g_readline->num2)
		{
			ft_putendl_fd(g_readline->history[g_readline->num1],
			g_readline->file_fd);
			g_readline->num1--;
		}
	}
	ft_clear_file();
}
