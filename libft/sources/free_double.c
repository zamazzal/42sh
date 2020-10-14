/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 02:41:26 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/02 22:12:22 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_double(char **tab)
{
	if (!tab)
		return ;
	if (tab[1])
		free_double(&tab[1]);
	ft_strdel(&tab[0]);
}