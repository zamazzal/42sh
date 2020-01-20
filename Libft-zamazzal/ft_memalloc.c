/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 13:03:25 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/16 18:14:55 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_mmalloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr)
		ft_bzero(ptr, size);
	else
		exit(1);
	return (ptr);
}
