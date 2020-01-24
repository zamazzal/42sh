/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_built_e.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:06:21 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/21 15:39:31 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_execute_editor(void)
{
	pid_t	id;
	int		status;

	if (!g_readline->e)
		g_readline->editor = ft_strdup("/usr/bin/vim");
	char	*arg[] = {g_readline->editor, "random_save", NULL};

	id = fork();
	if (id == 0)
		execve(g_readline->editor, arg, g_environ);
	else
		waitpid(id, &status, 0);
}

void	ft_hist_e(void)
{
	if (ft_check_flag() == -1)
		return ;
	g_readline->file_fd = open("random_save", O_RDWR | O_CREAT);
	if (!g_readline->num2)
	{
		if (!g_readline->n)
			ft_putnbr_fd(g_readline->num1, g_readline->file_fd);
		ft_putstr_fd("   ", g_readline->file_fd);
		ft_putendl_fd(g_readline->history[g_readline->num1],
		g_readline->file_fd);
	}
	else
		while (g_readline->num1 <= g_readline->num2
		&& g_readline->history[g_readline->num1])
		{
			if (!g_readline->n)
				ft_putnbr_fd(g_readline->num1, g_readline->file_fd);
			ft_putstr_fd("   ", g_readline->file_fd);
			ft_putendl_fd(g_readline->history[g_readline->num1],
			g_readline->file_fd);
			g_readline->num1++;
		}
	ft_clear_file();
}

void	ft_hist_er(void)
{
	if (ft_check_flag() == -1)
		return ;
	g_readline->file_fd = open("random_save", O_RDWR | O_CREAT);
	if (!g_readline->num2)
	{
		if (!g_readline->n)
			ft_putnbr_fd(g_readline->num1, g_readline->file_fd);
		ft_putstr_fd("   ", g_readline->file_fd);
		ft_putendl_fd(g_readline->history[g_readline->num1],
		g_readline->file_fd);
	}
	else
		while (g_readline->num1 >= g_readline->num2
		&& g_readline->history[g_readline->num1])
		{
			if (!g_readline->n)
				ft_putnbr_fd(g_readline->num1, g_readline->file_fd);
			ft_putstr_fd("   ", g_readline->file_fd);
			ft_putendl_fd(g_readline->history[g_readline->num1],
			g_readline->file_fd);
			g_readline->num1--;
		}
	ft_clear_file();
}
