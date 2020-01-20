/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 12:46:17 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/16 22:10:58 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char *str;

	if (!src)
		return (NULL);
	str = (char *)ft_mmalloc(sizeof(char) * (ft_strlen(src) + 1));
	return (ft_strcpy(str, src));
}
