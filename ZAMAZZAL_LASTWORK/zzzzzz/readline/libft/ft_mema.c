/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mema.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 05:30:47 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/23 22:38:22 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_mema(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr)
		ft_bzero(ptr, size);
	else
		exit(1);
	return (ptr);
}

