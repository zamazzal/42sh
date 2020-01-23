/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_changestr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 05:56:01 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/23 06:02:38 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_changestr(char **str, char *value, int start, int end)
{
	char	*tmp;
	char	*newstr;

	newstr = ft_strsub(*str, 0, start);
	newstr = ft_jandf(newstr, value, 1, 0);
	tmp = ft_strsub(*str, start + end, ft_strlen(*str));
	newstr = ft_jandf(newstr, tmp, 1, 1);
	ft_strdel(str);
	*str = newstr;
}
