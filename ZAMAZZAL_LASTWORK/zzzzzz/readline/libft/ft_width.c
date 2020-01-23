/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:48:11 by hessabra          #+#    #+#             */
/*   Updated: 2019/03/10 05:35:05 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_width(const char *format, int *i, int r)
{
	char	*c;
	int		j;

	if (format[*i] == '*')
	{
		(*i)++;
		return (-1);
	}
	while (ft_isdigit(format[*i]))
		(*i)++;
	c = ft_strsub(format, r, (size_t)*i);
	j = ft_atoi(c);
	free(c);
	if (j == 0)
		return (1);
	return (j);
}
