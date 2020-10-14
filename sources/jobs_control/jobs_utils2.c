/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 23:46:27 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/15 23:50:42 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			print_command(t_parse *lst)
{
	if (!lst)
		return ;
	ft_putstr(lst->cmd);
	if (lst->pipe)
	{
		ft_putstr(" | ");
		print_command(lst->pipe);
	}
	if (lst->if_seccess)
	{
		ft_putstr(" && ");
		print_command(lst->if_seccess);
	}
	if (lst->if_fail)
	{
		ft_putstr(" || ");
		print_command(lst->if_fail);
	}
}

void			print_command_p(t_parse *lst)
{
	if (!lst)
		return ;
	ft_putstr(lst->cmd);
	if (lst->pipe)
	{
		ft_putstr(" | ");
		print_command(lst->pipe);
	}
}
