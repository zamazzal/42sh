/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jandf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 12:09:15 by hessabra          #+#    #+#             */
/*   Updated: 2019/10/10 20:52:29 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char						*ft_jandf(char *a, char *b, int fa, int fb)
{
	char					*res;

	res = ft_strjoin(a, b);
	if (fa == 1)
		ft_strdel(&a);
	if (fb == 1)
		ft_strdel(&b);
	return (res);
}
