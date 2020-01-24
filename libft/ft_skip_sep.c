/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_sep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:28:00 by oboualla          #+#    #+#             */
/*   Updated: 2019/12/15 17:33:08 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_skip_sep(const char *str, char *sep)
{
	int i;
	int j;
	int count_sep;

	if (!str || !sep)
		return (0);
	count_sep = 0;
	j = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (sep[j])
		{
			if (str[count_sep] == sep[j])
				count_sep++;
			j++;
		}
		i++;
	}
	return (count_sep);
}